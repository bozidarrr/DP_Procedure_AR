using System;
using System.Configuration;
using System.IO;
using System.Linq;

namespace InstanceGenerator
{
    class Program
    {
        static bool KreirajTestInput(string lokacijaTesta, string imeTesta, int brojKutija, int brojKuglica)
        {
            if (1 > brojKuglica || 1 > brojKutija)
                return false;

            string putanjaDoFajla = Path.Combine(lokacijaTesta, (imeTesta + ".test"));

            Console.WriteLine("Kreiranje testa {0}", putanjaDoFajla);


            if (File.Exists(putanjaDoFajla))
            {
                File.Delete(putanjaDoFajla);
            }

            using (StreamWriter pisac = new StreamWriter(putanjaDoFajla, false))
            {
                pisac.WriteLine("; Da li je moguce rasporediti {0} kuglica u {1} kutija,", brojKuglica, brojKutija);
                pisac.WriteLine("; tako da sve kuglice budu rasporedjene u kutije");
                pisac.WriteLine("; i da ni u jednoj kutiji ne bude vise od jedne kuglice");
                pisac.WriteLine();

                pisac.WriteLine("; Promenljiva xij nosi istinitosnu vrednost recenice: \"Kuglica sa rednim brojem i se nalazi u kutiji j\"");

                pisac.WriteLine("; Svaka kuglica je u nekoj od kutija");
                // xi1 \/ xi2 \/ xi3 \/ ... \/ xin
                for (int i = 1; i <= brojKuglica; i++)
                {
                    string formula = string.Format("x_{0}_{1}", i, 1);
                    for (int j = 2; j <= brojKutija; j++)
                    {
                        formula += string.Format(", x_{0}_{1}", i, j);
                    }
                    pisac.WriteLine(formula);
                }
                pisac.WriteLine();

                pisac.WriteLine("; Ne postoje dve kuglice koje su u istoj kutiji");
                // !xji \/ ! xki
                for (int i = 1; i < brojKutija; i++)
                {
                    for (int j = 1; j < brojKuglica; j++)
                    {
                        for (int k = j + 1; k < brojKuglica; k++)
                        {
                            pisac.WriteLine("!x_{1}_{0}, !x_{2}_{0}", i, j, k);
                        }
                    }
                }
                pisac.WriteLine();

                pisac.WriteLine("; Ne postoje dve kutije koje sadrze istu kuglicu");
                // !xji \/ ! xki
                for (int i = 1; i < brojKuglica; i++)
                {
                    for (int j = 1; j < brojKutija; j++)
                    {
                        for (int k = j + 1; k < brojKutija; k++)
                        {
                            pisac.WriteLine("!x_{0}_{1}, !x_{0}_{2}", i, j, k);
                        }
                    }
                }
                pisac.WriteLine();
                pisac.WriteLine(new string('-',50));
            }

            return true;
        }

        static void Main(string[] args)
        {
            string lokacijaTesta = ConfigurationManager.AppSettings["lokacija"];

            if (!Directory.Exists(lokacijaTesta))
            {
                Console.WriteLine("Kreiranje direktorijuma za testove");
                Directory.CreateDirectory(lokacijaTesta);
            }


            Console.WriteLine("Kreiranje testova");

            foreach (var test in ConfigurationManager.AppSettings.AllKeys.Where(key => !key.Equals("lokacija", StringComparison.InvariantCultureIgnoreCase)).Select(key => ConfigurationManager.AppSettings[key]).ToArray())
            {
                var podaci = test.Split(',');
                if (podaci == null || podaci.Length < 3)
                {
                    Console.WriteLine("Nije moguce dobiti trazeni podatak iz konfiguracionog fajla");
                    continue;
                }

                string imeTesta = podaci[0];
                int brojKutija, brojKuglica;

                if (!int.TryParse(podaci[1], out brojKutija) || !int.TryParse(podaci[2], out brojKuglica))
                {
                    Console.WriteLine("Nije moguce odrediti uredjeni par brojeva, na osnovu podataka ({0},{1})", podaci[0], podaci[1]);
                    continue;
                }

                if (!KreirajTestInput(lokacijaTesta, imeTesta, brojKutija, brojKuglica))
                {
                    Console.WriteLine("Greska pri kreiranju testa {0} na lokaciji {1}", imeTesta, lokacijaTesta);
                    continue;
                }
            }
            Console.WriteLine("Svi testovi kreirani :)");
            Console.WriteLine("Testove je moguce pronaci na lokaciji {0}", lokacijaTesta);
            Console.ReadKey();
        }
    }
}
