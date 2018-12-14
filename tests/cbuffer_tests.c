/*
** EPITECH PROJECT, 2018
** zappy server
** File description:
** lbuffer tester
*/

#include <criterion/criterion.h>
#include <string.h>

#include "lbuffer.h"

Test(lbuffer_create, zero_malloc)
{
	lbuffer_t buffer;

	cr_assert(lbuffer_create(&buffer, 0) == 0);
	lbuffer_destroy(&buffer);
	cr_assert(lbuffer_create(&buffer, 999999999999999999) == -1);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_write, buffer_1)
{
	lbuffer_t buffer;

	lbuffer_create(&buffer, 1);
	cr_assert(lbuffer_write(&buffer, "toto", 4) == 1);
	cr_assert(lbuffer_write(&buffer, "salut", 5) == 0);
	cr_assert(lbuffer_write(&buffer, "", 0) == 0);
	cr_assert(lbuffer_write(&buffer, "LAHO", 1) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_write, buffer_10)
{
	lbuffer_t buffer;

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_write(&buffer, "toto", 4) == 4);
	cr_assert(lbuffer_write(&buffer, "salut", 5) == 5);
	cr_assert(lbuffer_write(&buffer, "", 0) == 0);
	cr_assert(lbuffer_write(&buffer, "LAHO", 1) == 1);
	cr_assert(lbuffer_write(&buffer, "jambon", 6) == 0);
	cr_assert(lbuffer_write(&buffer, "LAHO", 2) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_read_write_ok, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_write(&buffer, "jambe", 5) == 5);
	cr_assert(lbuffer_write(&buffer, "poto", 4) == 4);
	cr_assert(lbuffer_read(&buffer, s, 3) == 3);
	cr_assert(strncmp(s, "jam", 3) == 0);
	cr_assert(lbuffer_read(&buffer, s, 5) == 5);
	cr_assert(strncmp(s, "bepot", 5) == 0);
	cr_assert(lbuffer_read(&buffer, s, 10) == 1);
	cr_assert(strncmp(s, "o", 1) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_read_too_long, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_write(&buffer, "banane", 6) == 6);
	cr_assert(lbuffer_read(&buffer, s, 10) == 6);
	cr_assert(strncmp(s, "banane", 6) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_write_too_long, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_write(&buffer, "potatoes la magnifique", 22) == 10);
	cr_assert(lbuffer_read(&buffer, s, 10) == 10);
	cr_assert(strncmp(s, "potatoes l", 10) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_write_full, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_write(&buffer, "salut les potes", 10) == 10);
	cr_assert(lbuffer_write(&buffer, "peau de banane", 7) == 0);
	cr_assert(lbuffer_read(&buffer, s, 10) == 10);
	cr_assert(strncmp(s, "salut les ", 10) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_read_empty, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_read(&buffer, s, 10) == 0);
	cr_assert(lbuffer_write(&buffer, "yolo", 4) == 4);
	cr_assert(lbuffer_read(&buffer, s, 4) == 4);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(lbuffer_read(&buffer, s, 4) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(lbuffer_read(&buffer, s, 10) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(lbuffer_read(&buffer, s, 345645) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_lsize, buffer_10)
{
	lbuffer_t buffer;
	char s[10];

	lbuffer_create(&buffer, 10);
	cr_assert(lbuffer_lsize(&buffer) == 10);
	cr_assert(lbuffer_write(&buffer, "salut", 5) == 5);
	cr_assert(lbuffer_lsize(&buffer) == 5);
	cr_assert(lbuffer_write(&buffer, "toto", 4) == 4);
	cr_assert(lbuffer_lsize(&buffer) == 1);
	cr_assert(lbuffer_read(&buffer, s, 3) == 3);
	cr_assert(lbuffer_lsize(&buffer) == 4);
	cr_assert(lbuffer_write(&buffer, "titi", 4) == 4);
	cr_assert(lbuffer_lsize(&buffer) == 0);
	cr_assert(lbuffer_read(&buffer, s, 6) == 6);
	cr_assert(lbuffer_lsize(&buffer) == 6);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_rdwr_not_char, various_tests)
{
	lbuffer_t buffer;
	int a = 34;
	long b = 21;
	double c = 3.14;

	lbuffer_create(&buffer, 4096);
	cr_assert(lbuffer_write(&buffer, &a, sizeof(a)) == sizeof(a));
	cr_assert(lbuffer_write(&buffer, &b, sizeof(b)) == sizeof(b));
	cr_assert(lbuffer_write(&buffer, &c, sizeof(c)) == sizeof(c));

	cr_assert(lbuffer_read(&buffer, &a, sizeof(a)) == sizeof(a));
	cr_assert(lbuffer_read(&buffer, &b, sizeof(b)) == sizeof(b));
	cr_assert(lbuffer_read(&buffer, &c, sizeof(c)) == sizeof(c));

	cr_assert(a == 34);
	cr_assert(b == 21);
	cr_assert(c == 3.14);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_getbytes, various_tests)
{
	lbuffer_t buffer;
	char toto[] = "age=14:taille=1.45!oui ";
	char *output;

	lbuffer_create(&buffer, 128);
	lbuffer_write(&buffer, toto, strlen(toto));
	cr_assert(lbuffer_getbytes(&buffer, &output, "age=") == 4);
	cr_assert(strcmp(output, "age=") == 0);
	free(output);
	cr_assert(lbuffer_getbytes(&buffer, &output, ":") == 3);
	cr_assert(strcmp(output, "14:") == 0);
	free(output);
	cr_assert(lbuffer_getbytes(&buffer, &output, "taille=") == 7);
	cr_assert(strcmp(output, "taille=") == 0);
	free(output);
	cr_assert(lbuffer_getbytes(&buffer, &output, "!") == 5);
	cr_assert(strcmp(output, "1.45!") == 0);
	free(output);
	cr_assert(lbuffer_getbytes(&buffer, &output, " ") == 4);
	cr_assert(strcmp(output, "oui ") == 0);
	free(output);
	lbuffer_destroy(&buffer);
}

Test(lbuffer_resize, various_tests)
{
	lbuffer_t buffer;
	char toto[] = "Je suis un tester de fonctions";
	char test[sizeof(toto)] = { 0 };

	lbuffer_create(&buffer, sizeof(toto) - 10);
	cr_assert(lbuffer_write(&buffer, toto, sizeof(toto)) == sizeof(toto) - 10);
	cr_assert(lbuffer_resize(&buffer, sizeof(toto)) == 0);
	cr_assert(buffer.size == sizeof(toto));
	lbuffer_read(&buffer, test, sizeof(test));
	cr_assert(strncmp(test, toto, sizeof(toto) - 10) == 0);
	cr_assert(lbuffer_write(&buffer, toto, sizeof(toto)) == sizeof(toto));
	cr_assert(lbuffer_read(&buffer, test, sizeof(test)) == sizeof(test));
	cr_assert(strncmp(test, toto, sizeof(test)) == 0);
}
