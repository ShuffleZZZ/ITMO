# Расчетная работа №1 по курсу "Современная теория информации"

Расширенным кодом Голея называется (24, 12, 8) код с порождающей матрицей:

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | a    | b    | c    | d    | e    | f    | g    | h    | i    | j    | k    | l    | m    | n    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 1    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 1    | 1    | 1    | 1    | 1    | 0    | 0    | 0    | 1    |
| 0    | 1    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 1    | 0    | 0    | 1    | 1    | 1    | 0    | 1    | 1    |
| 0    | 0    | 1    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 1    | 0    | 1    | 0    | 1    | 0    | 1    | 1    | 1    |
| 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 1    | 1    | 1    | 0    | 0    | 0    | 0    | 1    | 1    | 1    | 0    |
| 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 1    | 0    | 0    | 1    | 1    | 1    | 1    | 1    |
| 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 1    | 0    | 0    | 1    | 1    | 1    | 1    | 0    | 1    | 0    |
| 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 0    | 1    | 1    | 0    | 0    | 0    | 1    | 1    | 0    | 0    | 1    | 1    | 1    |
| 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 1    | 1    | 1    | 0    | 1    | 1    | 0    | 1    | 0    | 1    | 0    | 0    |
| 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 1    | 0    | 1    | 1    | 1    | 0    | 0    | 1    | 1    | 0    | 1    |
| 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 0    | 0    | 1    | 1    | 1    | 0    | 1    | 1    | 1    | 1    | 0    | 0    |
| 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 0    | 0    | 1    | 1    | 1    | 1    | 1    | 1    | 0    | 0    | 0    | 1    | 0    |
| 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 0    | 1    | 1    | 1    | 1    | 0    | 1    | 0    | 1    | 0    | 1    | 0    | 0    | 1    |

Можно показать, что для декодирования любых трех ошибок достаточно рассмотреть следующие перестановки столбцов, для каждой из которых информационная совокупность (ИС) формируется из первых 12 столбцов:

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | a    | b    | c    | d    | e    | f    | g    | h    | i    | j    | k    | l    | m    | n    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 0    | 1    | 2    | c    | d    | e    | 3    | 4    | 5    | f    | g    | h    | i    | j    | k    | 6    | 7    | 8    | l    | m    | n    | 9    | a    | b    |
| 0    | 1    | 2    | i    | j    | k    | c    | d    | e    | 6    | 7    | 8    | l    | m    | n    | 3    | 4    | 5    | 9    | a    | b    | f    | g    | h    |
| 0    | 1    | 2    | l    | m    | n    | i    | j    | k    | 3    | 4    | 5    | 9    | a    | b    | c    | d    | e    | f    | g    | h    | 6    | 7    | 8    |
| 0    | 1    | 2    | 9    | a    | b    | l    | m    | n    | c    | d    | e    | f    | g    | h    | i    | j    | k    | 6    | 7    | 8    | 3    | 4    | 5    |
| 0    | 1    | 2    | f    | g    | h    | 9    | a    | b    | i    | j    | k    | 6    | 7    | 8    | l    | m    | n    | 3    | 4    | 5    | c    | d    | e    |
| 0    | 1    | 2    | 6    | 7    | 8    | f    | g    | h    | l    | m    | n    | 3    | 4    | 5    | 9    | a    | b    | c    | d    | e    | i    | j    | k    |
| c    | d    | e    | f    | g    | h    | i    | j    | k    | l    | m    | n    | 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | a    | b    |
| i    | j    | k    | 6    | 7    | 8    | l    | m    | n    | 9    | a    | b    | 0    | 1    | 2    | c    | d    | e    | 3    | 4    | 5    | f    | g    | h    |
| l    | m    | n    | 3    | 4    | 5    | 9    | a    | b    | f    | g    | h    | 0    | 1    | 2    | i    | j    | k    | c    | d    | e    | 6    | 7    | 8    |
| 9    | a    | b    | c    | d    | e    | f    | g    | h    | 6    | 7    | 8    | 0    | 1    | 2    | l    | m    | n    | i    | j    | k    | 3    | 4    | 5    |
| f    | g    | h    | i    | j    | k    | 6    | 7    | 8    | 3    | 4    | 5    | 0    | 1    | 2    | 9    | a    | b    | l    | m    | n    | c    | d    | e    |
| 6    | 7    | 8    | l    | m    | n    | 3    | 4    | 5    | c    | d    | e    | 0    | 1    | 2    | f    | g    | h    | 9    | a    | b    | i    | j    | k    |
| 3    | 4    | 5    | 9    | a    | b    | c    | d    | e    | i    | j    | k    | 0    | 1    | 2    | 6    | 7    | 8    | f    | g    | h    | l    | m    | n    |

Необходимо продекодировать нижеприведенные вектора в коде Голея. В ответе необходимо указать соответствующее кодовое слово, вектор ошибки (в виде номеров ошибочных позиций), а также промежуточные результаты рассмотрения вышеприведенных информационных совокупностей. Пример оформления ответа:

- Иванов Иван Иванович, гр. M1234
- Вариант: 0
- Кодовое слово: 000000000000000000000000
- Вектор ошибки: 1abc
- <Для каждой ИС нужно привести порождающую матрицу, приведенную к систематическому виду на позициях из этой ИС, и соответствующие оценки вектора ошибки>