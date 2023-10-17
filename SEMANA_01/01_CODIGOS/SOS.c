void setup()
{
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
}

void loop()
{
    // Sei que daria pra fazer com uma função e diminuir as linhas de código, mas eu tô com preguiça, prof =[
    // Fazer o S com três piscadas rápidas
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }

    // Fazer o O com três piscadas Lentas
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(2, HIGH);
        delay(2000);
        digitalWrite(2, LOW);
        delay(500);
    }

    // Fazer o S com três piscadas rápidas
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);
        delay(500);
    }

    delay(5000);
}
