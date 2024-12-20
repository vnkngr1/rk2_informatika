# Задача 8.1: Двоичная арифметика

## Условие:

Два числа даны в двоичной системе счисления: `A = 101101` и `B = 110011`

Напишите программу на любом языке программирования (или вручную выполните вычисление), которая:

1.	Выполняет побитовую операцию AND для чисел A и B.
 
2.	Вычисляет сумму чисел A и B в двоичной системе.

## Решение:

В файле `task1.h`

# Задача 8.2: Создайте скрипт find_files.sh

## Условия:

1.	Принимает два аргумента:

•	Путь к директории.

•	Расширение файлов (например, txt, log, sh).

2.	Проверяет, что оба аргумента переданы. Если нет, выводит сообщение: `Пожалуйста, укажите директорию и расширение файлов.`

3.	Проверяет, существует ли указанная директория. Если нет, выводит сообщение: `Директория не найдена.`

4.	Если директория существует, ищет все файлы с указанным расширением в этой директории и ее поддиректориях.

5.	Выводит список найденных файлов или сообщение: `Файлы с расширением <расширение> не найдены.`

## Решение:

```
#!/bin/bash

# Проверяем, верно ли переданы аргументы
if [ $# -ne 2 ]; then
  echo "Пожалуйста, укажите директорию и расширение файлов."
  exit 1
fi

DIRECTORY=$1
EXTENSION=$2

# Проверяем, существует ли указанная директория
if [ ! -d "$DIRECTORY" ]; then
  echo "Директория не найдена."
  exit 1
fi

# Ищем файлы с указанным расширением
FOUND_FILES=$(find "$DIRECTORY" -type f -name "*.$EXTENSION")

# Проверяем, найдены ли файлы и выводим их
if [ -z "$FOUND_FILES" ]; then
  echo "Файлы с расширением $EXTENSION не найдены."
else
  echo "Найдены файлы с расширением $EXTENSION:"
  echo "$FOUND_FILES"
fi
```

# Задача 8.3

В базе данных имеется таблица employees :

<img width="1141" alt="Снимок экрана 2024-12-20 в 18 49 22" src="https://github.com/user-attachments/assets/6e2690aa-bc12-4003-9df2-d4f7f55e63f1" />

Напишите SQL-запрос, который выводит всех сотрудников из отдела IT, устроившихся после 2020 года, отсортированных по заработной плате в порядке убывания.

## Решение:

```
SELECT *
FROM employees
WHERE department = 'IT'
  AND hire_date > '2020-01-01'
ORDER BY salary DESC;
```

# Задача 8.4

## Условия:

Создайте систему для учета операций с товарами на складе с использованием триггера и хранимой процедуры.

1. Создайте таблицы:
   
### products — товары на складе

•	id (serial, primary key): идентификатор товара.

•	name (varchar): название товара.

•	quantity (integer): количество товара.

### operations_log — журнал операций с товарами:

•	id (serial, primary key): идентификатор записи.

•	product_id (integer, foreign key): идентификатор товара.

•	operation (varchar): тип операции (ADD или REMOVE).

•	quantity (integer): количество.
	
•	operation_date (timestamp): дата операции (по умолчанию текущая).

2. Реализуйте хранимую процедуру update_stock(product_id INT, operation VARCHAR, quantity INT):

•	Если operation = 'ADD', увеличьте количество товара.

•	Если operation = 'REMOVE', уменьшите количество товара, проверив, чтобы оно не стало отрицательным.

•	Добавьте запись в таблицу operations_log.

## Решение:

### 1. Создание таблиц:

```
-- Таблица для хранения товаров
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    quantity INTEGER NOT NULL DEFAULT 0
);

-- Таблица для хранения журнала операций
CREATE TABLE operations_log (
    id SERIAL PRIMARY KEY,
    product_id INTEGER REFERENCES products(id),
    operation VARCHAR(10) CHECK (operation IN ('ADD', 'REMOVE')),
    quantity INTEGER NOT NULL,
    operation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### 2. Процедура update_stock:

```
CREATE OR REPLACE FUNCTION update_stock(product_id INT, operation VARCHAR, quantity INT)
RETURNS VOID AS $$
BEGIN
    -- Проверка операции ADD
    IF operation = 'ADD' THEN
        UPDATE products
        SET quantity = quantity + quantity
        WHERE id = product_id;

    -- Проверка операции REMOVE
    ELSIF operation = 'REMOVE' THEN
        UPDATE products
        SET quantity = quantity - quantity
        WHERE id = product_id;

        -- Проверка на отрицательное значение количества
        IF (SELECT quantity FROM products WHERE id = product_id) < 0 THEN
            RAISE EXCEPTION 'Количество товара не может быть отрицательным';
        END IF;
    ELSE
        RAISE EXCEPTION 'Неизвестная операция: %', operation;
    END IF;

    -- Добавление записи в журнал операций
    INSERT INTO operations_log(product_id, operation, quantity)
    VALUES (product_id, operation, quantity);

END;
$$ LANGUAGE plpgsql;
```

# Задание 8.5

## Условия:

Создайте программу на C++, которая моделирует работу банка.

1. Создайте класс `BankAccount`, который включает:

Поля:

•	номер_счёта (номер счёта клиента).

•	имя_владельца (имя клиента).

•	баланс (текущий баланс на счёте).

Методы:

•	Конструктор: для инициализации данных.

•	Метод deposit: для пополнения баланса.

•	Метод withdraw: для снятия средств с баланса.

2. Создайте производный класс `SavingsAccount`, который добавляет:

Поле:

•	процентная_ставка (процентная ставка по вкладу).

Метод:

•	Метод для начисления процентов: увеличивает баланс в соответствии с процентной ставкой.

3. В функции main():
   
•	Создайте объекты классов BankAccount и SavingsAccount.
	
•	Выполните операции пополнения, снятия и начисления процентов для проверки работы программы.

## Решение

Решение лежит в `main.cpp`

