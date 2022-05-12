/*
1)Для начала из папки в системе, где находятся файлы firct.c и second.c
    мы компилируем их командами gcc first.c -o first и gcc second.c -o second соответственно.
2) Далее мы должны открыть второй терминал в этой же папке, чтобы с этими двумя программами можно было работать 
    по-отдельности. 
3) Сначала в одном терминале запускаем первую программу командой ./first . Должна появится строка "PID = id_процесса_первой_программы", 
    (допустим "PID = 1599"), а также начать с интервалом в 3 секунды бесконечно выводится строка "Nothing is happening".
4) В другом терминале запускаем вторую программу командой ./second PID_первой_программы SIGUSR1/SIGUSR2.
5) Например, если PID первой программы равен 1599, и также мы хотим отправить первой программе SIGUSR2, чтобы она стала
    выводить строку "SIGUSR2 happened", то при запуске второй программы мы пишем ./second 1599 SIGUSR2
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char* lines[] = {
	"Nothing is happening",
	"SIGUSR1 happened",
	"SIGUSR2 happened"
};

void changer(int input);
int i = 0;

int main(void)
{
    printf("PID = %d\n", getpid());
    signal(SIGUSR1, changer);
    signal(SIGUSR2, changer);
    while (1)
    {
		char* line = lines[i];
		printf("%s\n", line);
		sleep(3);
	}
    return 0;
}

void changer(int input)
{
    switch (input)
    {
    case SIGUSR1: 
    i = 1; break;

	case SIGUSR2: 
    i = 2; break;

    default: 
    i = 0;
    }
}

