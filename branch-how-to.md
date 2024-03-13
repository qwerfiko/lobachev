## Создание веток
Создание новой ветки в склонированном репозиториии осуществляется командой
```shell
git branch branch_name
```

## Переключение между ветками
Для переключения на другую ветку используется команда
```shell
git checkout branch_name
```
После переключения на ветку, работа в ней осуществляется как обычно.

## Объединение веток
Чтобы объединить текущую ветку с веткой `master`, нужно ввести команду
```shell
git merge branch_name
```
Если в процессе возникла непредвиденная ошибка, отменить слияние можно командой
```shell
git merge --abort
```

## Загрузка изменений из веток
Чтобы загрузить изменения во всех ветках, нужно ввести команду
```shell
git fetch
```
Для просмотра всех веток в репозитории используется команда
```shell
git branch --all
```