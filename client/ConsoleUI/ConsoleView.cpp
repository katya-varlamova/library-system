//
// Created by Екатерина on 22.05.2022.
//

#include "ConsoleView.h"
void ConsoleView::inputString(const char * intro, std::string &s)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    char *buf = (char *) malloc(70);
    printf("%s", intro);
    fgets(buf, 70, stdin);
    buf[strlen(buf) - 1] = '\0';
    s = buf;
    free(buf);
}
void ConsoleView::outputString(std::string s)
{
    printf("%s", s.c_str());
}
void ConsoleView::inputNum(const char *intro, int &n)
{
    printf("%s", intro);
    scanf("%d", &n);
}