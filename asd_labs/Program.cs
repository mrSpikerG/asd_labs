using asd_labs;


int tableSize = 7;
int keyInt = 10;
string keyString = "Hello";
int check = 0;
do {
    Console.WriteLine("0 - Exit");
    Console.WriteLine("1 - Divide");
    Console.WriteLine("2 - Multiply");
    Console.WriteLine("3 - string key");
    check = int.Parse(Console.ReadLine());

    if (check == 1) {
        Console.WriteLine("Write to hash by divide");
        keyInt =int.Parse( Console.ReadLine());
        int divisionHash = HashFunction.DivisionHash(keyInt, tableSize);
        Console.WriteLine($"Хеш-значення для ключа {keyInt} методом ділення: {divisionHash}");


    } else if (check == 2) {
        Console.WriteLine("Write to hash by divide");
        keyInt = int.Parse(Console.ReadLine());

        int multiplicationHash = HashFunction.MultiplicationHash(keyInt, tableSize);
        Console.WriteLine($"Хеш-значення для ключа {keyInt} методом множення: {multiplicationHash}");

    } else if (check == 3) {        
        Console.WriteLine("Write key string: ");
        keyString = Console.ReadLine();
        Console.WriteLine("Write constint: ");
        int const_a = int.Parse(Console.ReadLine());
        double stringHash = HashFunction.StringHash(keyString, tableSize,const_a);
        Console.WriteLine($"Хеш-значення для рядкового ключа '{keyString}': {stringHash}");
    }



} while (check != 0);











