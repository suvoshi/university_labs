using System;

InternetOperator op1 = new("op1", 500, 20000);
op1.Password = "123qwerty";

InternetOperator op2 = new("op2", 654, 34567);
op2.Password = "secretpassword";


op1.DisplayInfo();
op1.DisplayProfit();

op2.DisplayInfo();
op2.DisplayProfit();

public class InternetOperator
{
    public string Name { get; set; }
    public float Cost { get; set; }
    public int Users { get; set; }

    private string _password;

    public InternetOperator(string name, float cost, int users)
    {   
        if (name.Length == 0)
        {
            throw new ArgumentException("Не может быть пустым");
        }
        Name = name;

        if (cost <= 0)
        {
            throw new ArgumentException("Не может быть отрицательным или равным 0");
        }
        Cost = cost;

        if (users < 0)
        {
            throw new ArgumentException("Не может быть отрицательным");
        }
        Users = users;
    }

    public string Password
    {
        set
        {
            _password = value;
        }
    }

    public void DisplayInfo()
    {
        Console.WriteLine($"Название оператора: {Name}, Цена: {Cost}, Количество пользователей: {Users}");
    }

    public void DisplayProfit()
    {
        Console.WriteLine($"Профит компании: {Cost*Users}");
    }
}