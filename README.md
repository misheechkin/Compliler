# Лабораторная работа №3. Разработка синтаксического анализатора (парсера)
## Цель работы: Изучить назначение синтаксического анализатора. Спроектировать алгоритм и выполнить программную реализацию парсера.
## Персональный вариант:
Компилятор ассоциативного массива `map <string,int> dsa;` языка C++.\
## Грамматика:"
<MAP> -> 'map' <OB> 
<OB> -> '<' <KEYTYPE> 
<KEYTYPE> -> type <COMM> 
<COMM> -> ',' <VALUETYPE>  
<VALUETYPE > -> type <CB> 
<CB> -> '>' <VARREM> 
< VARREM > -> letter <VARREM> 
< VARREM > -> ';' 
<letter> → "a" | "b" | "c" | ... | "z" | "A" | "B" | "C" | ... | "Z" | 
<type> → "int" | "string" | "double" | "float" | 
## Граф:
![img](https://github.com/user-attachments/assets/aaa6cff0-5ab4-44b9-ba63-1ad8291194c9)

### Тестовые примеры:
![Вставленное изображение](https://github.com/user-attachments/assets/7494bc8d-f214-41e3-a780-662ac158791e)
![image](https://github.com/user-attachments/assets/674aece2-d825-46a5-bec7-c62ff59da252)
![image](https://github.com/user-attachments/assets/7bb44430-cf85-4bf7-902b-db2d8d38b1aa)
![image](https://github.com/user-attachments/assets/ebdc767e-da74-410a-8816-8e9c614316e6)


# Лабораторная работа №4. Разработка синтаксического анализатора (парсера)
## Цель работы: Изучить назначение синтаксического анализатора. Спроектировать алгоритм и выполнить программную реализацию парсера.
## Персональный вариант:
Компилятор ассоциативного массива `map <string,int> dsa;` языка C++.\
## Грамматика:"
<MAP> -> 'map' <OB> 
<OB> -> '<' <KEYTYPE> 
<KEYTYPE> -> type <COMM> 
<COMM> -> ',' <VALUETYPE>  
<VALUETYPE > -> type <CB> 
<CB> -> '>' <VARREM> 
< VARREM > -> letter <VARREM> 
< VARREM > -> ';' 
<letter> → "a" | "b" | "c" | ... | "z" | "A" | "B" | "C" | ... | "Z" | 
<type> → "int" | "string" | "double" | "float" | 
## Граф:
![img](https://github.com/user-attachments/assets/aaa6cff0-5ab4-44b9-ba63-1ad8291194c9)

### Тестовые примеры:
![Вставленное изображение](https://github.com/user-attachments/assets/7494bc8d-f214-41e3-a780-662ac158791e)
![image](https://github.com/user-attachments/assets/674aece2-d825-46a5-bec7-c62ff59da252)
![image](https://github.com/user-attachments/assets/7bb44430-cf85-4bf7-902b-db2d8d38b1aa)
![image](https://github.com/user-attachments/assets/ebdc767e-da74-410a-8816-8e9c614316e6)



# Лабораторная работа №5. Включение семантики в анализатор. Создание внутренней формы представления программы.
## Цель работы: Дополнить анализатор, разработанный в рамках лабораторных работ, этапом формирования внутренней формы представления программы.
## Персональный вариант:
1 вариант. В качестве внутренней формы представления программы выберем польскую инверсную запись (ПОЛИЗ). Эта форма представления наглядна и достаточно проста для последующей интерпретации, которая может быть выполнена с использованием стека.

Задание:

1) Реализовать в текстовом редакторе поиск лексических и синтаксических ошибок для грамматики G[<E>]. Реализовать данную КС-граммматику методом рекурсивного спуска:

1. E → TA 

2. A → ε | + TA | - TA 

3. T → ОВ 

4. В → ε | *ОВ | /ОВ 

5. О → num | (E) 

6. num  → digit {digit}

2) Реализовать алгоритм записи арифметических выражений в ПОЛИЗ и алгоритм вычисления выражений в ПОЛИЗ.

### Примеры допустимых строк
- 6 + 7 + 10 * 4
- 5*5*5

### Тестовые примеры:
![image](https://github.com/user-attachments/assets/82303df0-c072-4736-bc18-35cb01f2fe84)
![image](https://github.com/user-attachments/assets/1f13c4a9-f3b5-4adb-903c-4e76ebace92d)
![image](https://github.com/user-attachments/assets/ec8cd089-c470-475b-a97f-b414526d9967)


