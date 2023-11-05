using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace asd_labs {
    internal class HashFunction {
        // Хеш-функція методом ділення
        public static int DivisionHash(int key, int tableSize) {
            if (tableSize <= 0)
                throw new ArgumentException("Розмір таблиці має бути більше 0.");

            return key % tableSize;
        }

        // Хеш-функція методом множення
        public static int MultiplicationHash(int key, int tableSize) {
            if (tableSize <= 0)
                throw new ArgumentException("Розмір таблиці має бути більше 0.");

            const double A = 0.618033988749895; // Константа "золотий відрізок"

            double temp = key * A;
            temp -= Math.Floor(temp);
            return (int)Math.Floor(tableSize * temp);
        }

        // Хеш-функція для рядкових ключів
        public static double StringHash(string key, int tableSize, int a) {
            if (tableSize <= 0)
                throw new ArgumentException("Розмір таблиці має бути більше 0.");

            double hash = 0;
            for (int i =0;i<key.Length;i++) {
                hash += (key[i] * Math.Pow(a,i)); // Можна вибрати інше просте число, наприклад, 31
            }

            return hash % tableSize;
        }
   
    }
}
