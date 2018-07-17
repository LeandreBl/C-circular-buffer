/*
** EPITECH PROJECT, 2018
** zappy server
** File description:
** cbuffer tester
*/

#include <criterion/criterion.h>
#include <string.h>

#include "lblcbuffer.h"

Test(cbuffer_create, zero_malloc)
{
	cbuffer_t buffer;

	cr_assert(cbuffer_create(&buffer, 0) == 0);
	cbuffer_destroy(&buffer);
	cr_assert(cbuffer_create(&buffer, 999999999999999999) == -1);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_write, buffer_1)
{
	cbuffer_t buffer;

	cbuffer_create(&buffer, 1);
	cr_assert(cbuffer_write(&buffer, "toto", 4) == 1);
	cr_assert(cbuffer_write(&buffer, "salut", 5) == 0);
	cr_assert(cbuffer_write(&buffer, "", 0) == 0);
	cr_assert(cbuffer_write(&buffer, "LAHO", 1) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_write, buffer_10)
{
	cbuffer_t buffer;

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_write(&buffer, "toto", 4) == 4);
	cr_assert(cbuffer_write(&buffer, "salut", 5) == 5);
	cr_assert(cbuffer_write(&buffer, "", 0) == 0);
	cr_assert(cbuffer_write(&buffer, "LAHO", 1) == 1);
	cr_assert(cbuffer_write(&buffer, "jambon", 6) == 0);
	cr_assert(cbuffer_write(&buffer, "LAHO", 2) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_read_write_ok, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_write(&buffer, "jambe", 5) == 5);
	cr_assert(cbuffer_write(&buffer, "poto", 4) == 4);
	cr_assert(cbuffer_read(&buffer, s, 3) == 3);
	cr_assert(strncmp(s, "jam", 3) == 0);
	cr_assert(cbuffer_read(&buffer, s, 5) == 5);
	cr_assert(strncmp(s, "bepot", 5) == 0);
	cr_assert(cbuffer_read(&buffer, s, 10) == 1);
	cr_assert(strncmp(s, "o", 1) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_read_too_long, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_write(&buffer, "banane", 6) == 6);
	cr_assert(cbuffer_read(&buffer, s, 10) == 6);
	cr_assert(strncmp(s, "banane", 6) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_write_too_long, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_write(&buffer, "potatoes la magnifique", 22) == 10);
	cr_assert(cbuffer_read(&buffer, s, 10) == 10);
	cr_assert(strncmp(s, "potatoes l", 10) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_write_full, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_write(&buffer, "salut les potes", 10) == 10);
	cr_assert(cbuffer_write(&buffer, "peau de banane", 7) == 0);
	cr_assert(cbuffer_read(&buffer, s, 10) == 10);
	cr_assert(strncmp(s, "salut les ", 10) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_read_empty, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_read(&buffer, s, 10) == 0);
	cr_assert(cbuffer_write(&buffer, "yolo", 4) == 4);
	cr_assert(cbuffer_read(&buffer, s, 4) == 4);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(cbuffer_read(&buffer, s, 4) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(cbuffer_read(&buffer, s, 10) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cr_assert(cbuffer_read(&buffer, s, 345645) == 0);
	cr_assert(strncmp(s, "yolo", 4) == 0);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_lsize, buffer_10)
{
	cbuffer_t buffer;
	char s[10];

	cbuffer_create(&buffer, 10);
	cr_assert(cbuffer_lsize(&buffer) == 10);
	cr_assert(cbuffer_write(&buffer, "salut", 5) == 5);
	cr_assert(cbuffer_lsize(&buffer) == 5);
	cr_assert(cbuffer_write(&buffer, "toto", 4) == 4);
	cr_assert(cbuffer_lsize(&buffer) == 1);
	cr_assert(cbuffer_read(&buffer, s, 3) == 3);
	cr_assert(cbuffer_lsize(&buffer) == 4);
	cr_assert(cbuffer_write(&buffer, "titi", 4) == 4);
	cr_assert(cbuffer_lsize(&buffer) == 0);
	cr_assert(cbuffer_read(&buffer, s, 6) == 6);
	cr_assert(cbuffer_lsize(&buffer) == 6);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_rdwr_not_char, various_tests)
{
	cbuffer_t buffer;
	int a = 34;
	long b = 21;
	double c = 3.14;

	cbuffer_create(&buffer, 4096);
	cr_assert(cbuffer_write(&buffer, &a, sizeof(a)) == sizeof(a));
	cr_assert(cbuffer_write(&buffer, &b, sizeof(b)) == sizeof(b));
	cr_assert(cbuffer_write(&buffer, &c, sizeof(c)) == sizeof(c));

	cr_assert(cbuffer_read(&buffer, &a, sizeof(a)) == sizeof(a));
	cr_assert(cbuffer_read(&buffer, &b, sizeof(b)) == sizeof(b));
	cr_assert(cbuffer_read(&buffer, &c, sizeof(c)) == sizeof(c));

	cr_assert(a == 34);
	cr_assert(b == 21);
	cr_assert(c == 3.14);
	cbuffer_destroy(&buffer);
}

Test(cbuffer_getbytes, various_tests)
{
	cbuffer_t buffer;
	char toto[] = "age=14:taille=1.45!";
	char *output;

	cbuffer_create(&buffer, 128);
	cbuffer_write(&buffer, toto, strlen(toto));
	cr_assert(cbuffer_getbytes(&buffer, &output, "=") == 4);
	cr_assert(strcmp(output, "age=") == 0);
	free(output);
	cr_assert(cbuffer_getbytes(&buffer, &output, ":") == 3);
	cr_assert(strcmp(output, "14:") == 0);
	free(output);
	cr_assert(cbuffer_getbytes(&buffer, &output, "=") == 7);
	cr_assert(strcmp(output, "taille=") == 0);
	free(output);
	cr_assert(cbuffer_getbytes(&buffer, &output, "!") == 5);
	cr_assert(strcmp(output, "1.45!") == 0);
	free(output);
	cbuffer_destroy(&buffer);
}