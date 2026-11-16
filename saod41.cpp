#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

const int n = 34;

const char *letters[n - 1] = {
    "а", "б", "в", "г", "д", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п",
    "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я", "ё"};

double p[n];
const char *a[n];
int length[n], c[n][64], sum = 0;

bool readText(const char *name)
{
    FILE *f = fopen(name, "rb");

    std::string text = "";
    char buf[1024];
    size_t sz;
    while ((sz = fread(buf, 1, sizeof(buf), f)) > 0)
    {
        text.append(buf, sz);
    }
    fclose(f);

    for (int i = 1; i < n; i++)
    {
        std::string letter = letters[i - 1];
        size_t pos = 0;
        while ((pos = text.find(letter, pos)) != std::string::npos)
        {
            p[i] += 1;
            sum++;
            pos += letter.length();
        }
    }
    return true;
}

void sortByProb()
{
    bool b = true;
    while (b)
    {
        b = false;
        for (int i = 2; i < n; i++)
            if (p[i - 1] < p[i])
            {
                double tp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = tp;
                const char *ta = a[i - 1];
                a[i - 1] = a[i];
                a[i] = ta;
                b = true;
            }
    }
}

void shanon()
{
    double q[n];
    p[0] = 0;
    q[0] = 0;
    for (int i = 1; i < n; i++)
    {
        q[i] = q[i - 1] + p[i];
        length[i] = (int)ceil(-log2(p[i]));
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= length[i]; j++)
        {
            q[i - 1] = q[i - 1] * 2;
            c[i][j] = (int)floor(q[i - 1]);
            if (q[i - 1] > 1)
                q[i - 1] = q[i - 1] - 1;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *name = "text.txt";
    for (int i = 1; i < n; i++)
    {
        a[i] = letters[i - 1];
        p[i] = 0;
    }
    if (!readText(name))
        return 1;

    sortByProb();

    double entropy = 0;
    for (int i = 1; i < n; i++)
    {
        p[i] /= (double)sum;
        if (p[i] > 0)
            entropy -= p[i] * log2(p[i]);
    }
    shanon();
    printf("\nКод Шеннона (букв в файле: %d)\n", sum);
    printf("----------------------------------------------------------\n");
    printf("| Символ | Вероятность | Кодовое слово          | Длина |\n");
    printf("----------------------------------------------------------\n");
    double lshanon = 0;
    for (int i = 1; i < n; i++)
    {
        if (p[i] == 0)
            continue;
        char word[64];
        for (int j = 1; j <= length[i]; j++)
            word[j - 1] = (char)('0' + c[i][j]);
        word[length[i]] = '\0';
        printf("|   %s   |  %9.6f   | %-22s |  %3d  |\n", a[i], p[i], word, length[i]);
        lshanon += length[i] * p[i];
    }
    printf("----------------------------------------------------------\n");
    printf("\nЭнтропия                      H   = %.5f бит/букву\n", entropy);
    printf("Средняя длина кодового слова  L   = %.5f бит/букву\n", lshanon);
    printf("Избыточность                  L-H = %.5f бит/букву\n", lshanon - entropy);
    double kraft = 0;
    for (int i = 1; i < n; i++)
    {
        if (p[i] > 0)
            kraft += pow(2.0, -length[i]);
    }
    printf("Крафт: %.6f %s\n", kraft, kraft <= 1.0 ? "Правильно" : "Неправильно");

    const char *text100 = "регулярный осмотр хранилищ выявляет проблемы вовремя и равномерный полив поддерживает развитие ростка";
    std::string encoded = "";
    int encodedLength = 0;

    for (size_t i = 0; i < strlen(text100); i++)
    {
        int idx = 0;
        for (int j = 1; j < n; j++)
        {
            if (text100[i] == a[j][0] && text100[i + 1] == a[j][1])
            {
                idx = j;
                break;
            }
        }

        if (idx > 0 && length[idx] > 0)
        {
            for (int j = 1; j <= length[idx]; j++)
            {
                encoded += (char)('0' + c[idx][j]);
                encodedLength++;
            }
        }
    }

    printf("\nКод: %s\n", encoded.c_str());
    printf("Длина: %d бит  Сжатие: %.2f\n", encodedLength, 1600.0 / encodedLength);

    return 0;
}