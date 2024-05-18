# Computer Club
## Инструкция по сборке
1. Клонировать гит репозиторий 
`git clone https://github.com/AntonZorikov/ComputerClub`
2. Перейти в корневую папку проекта
`cd ComputerClub`
3. Создать директорию для сборки и перейти в нее
`mkdir build`
`cd build`
4. Выполнить сборку
`cmake ..`
`ninja`
5. Запустить исполняемый файл
`./Program input.txt <имя .txt файла>`

## Инструкция по тестированию
1. Клонировать гит репозиторий 
`git clone https://github.com/AntonZorikov/ComputerClub`
2. Перейти в папку проекта содержащую тесты
`cd ComputerClub/tests`
3. Создать директорию для сборки и перейти в нее
`mkdir build`
`cd build`
4. Выполнить сборку
`cmake ..`
`ninja`
5. Запустить тестирование
`./Test`