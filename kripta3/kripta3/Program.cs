using System;
using System.Text;
using System.Linq;
using System.Security.Cryptography;
using System.IO;
using System.Security.Cryptography.X509Certificates;

namespace kripta3
{
    class Program
    {
        static void Keys(string name) 
        {
            var rsa = RSA.Create();

            //создаем запрос на сертификат 
            var request = new CertificateRequest("CN=b8103", rsa, HashAlgorithmName.SHA256, RSASignaturePadding.Pkcs1);

            //создаем самоподписанный сертификат на год
            var cert = request.CreateSelfSigned(DateTimeOffset.Now, DateTimeOffset.Now.AddYears(1));

            File.WriteAllBytes(name + ".cer", cert.Export(X509ContentType.Cert)); //открытый ключ
            File.WriteAllBytes(name + ".pem", cert.Export(X509ContentType.Pkcs12)); //закрытый ключ
        }

        static string CreateHash(string destination, string input, string algo)
        {
            var hash = HashAlgorithm.Create(algo); //алгоритм хеширования

            //хешируем и записываем в указанный файл
            byte[] hashb = hash.ComputeHash(File.ReadAllBytes(input));
            File.WriteAllBytes(destination, hashb);

            return string.Join("-", hashb.Select(x => x.ToString("x2")));
        }

        static HashAlgorithmName hash(string cert) //алгорит получения подписи сертификата
        {
            var PublicCert = new X509Certificate2(cert);
            var algo = PublicCert.SignatureAlgorithm.FriendlyName;
            HashAlgorithmName hashAlgorithmName;
            if (algo == "SHA1")
                hashAlgorithmName = HashAlgorithmName.SHA1;
            if (algo == "SHA256")
                hashAlgorithmName = HashAlgorithmName.SHA256;
            else
                hashAlgorithmName = HashAlgorithmName.MD5;
            return hashAlgorithmName;
        }
        static string CreateSign(string destination, string input, string pem, string c)
        {
            HashAlgorithmName hashAlgorithmName = hash(c);
            
            var cert = new X509Certificate2(pem);

            //берем закрытый ключ, подписываем файлы
            var sign = cert.GetRSAPrivateKey().SignData(File.ReadAllBytes(input), hashAlgorithmName, RSASignaturePadding.Pkcs1); 
            File.WriteAllBytes(destination, sign);

            return string.Join("-", sign.Select(x => x.ToString("x2")));
        }

        static string Verify(string name, string hashed, string signed, string cert)
        {
            
            var sign = File.ReadAllBytes(signed);
            var HashFile = File.ReadAllBytes(hashed);
            var file = File.ReadAllBytes(name);

            HashAlgorithmName hashAlgorithmName = hash(cert);

            var PublicCert = new X509Certificate2(cert);   
            var algo = PublicCert.PublicKey.Key.SignatureAlgorithm;

            //проверка подписи и хеша
            if (algo == "RSA")//для rsa
            {
                var PublicKey = PublicCert.GetRSAPublicKey();
                if (PublicKey.VerifyData(file, sign, hashAlgorithmName, RSASignaturePadding.Pkcs1) && PublicKey.VerifyHash(HashFile, sign, hashAlgorithmName, RSASignaturePadding.Pkcs1))
                    return (name + " VALID");
            }
            if (algo == "ECDsa")//для ecdsa
            {
                var PublicKey = PublicCert.GetECDsaPublicKey();
                if (PublicKey.VerifyData(file, sign, hashAlgorithmName) && PublicKey.VerifyHash(HashFile, sign))
                    return (name + " VALID");
            }
            return (name + " INVALID");
        }

        static void Main(string[] args)
        {
            Keys("certificat");
            Console.WriteLine(CreateHash("hash.hash", "1.jpg", "SHA-256"));
            Console.WriteLine(" ");
            Console.WriteLine(CreateSign("sign.sgn", "1.jpg", "certificat.pem", "certificat.cer"));
            Console.WriteLine(" ");
            Console.WriteLine(Verify("1.jpg", "hash.hash", "sign.sgn", "certificat.cer"));
            //Console.WriteLine(Verify("img10_1.jpg","hash.txt","sign.txt", "cert.cer"));
        }
    }
}
