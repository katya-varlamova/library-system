# Library system

## Идея проекта

Рзработать библиотечную систему, которая позволит читателям получать информацию о доступных книгах в разных библиотеках, а библиотекарям - выдвать и принимать книги.

## Предметная область

Библиотека - это учреждение, собирающее и осуществляющее хранение книг и иных печатных изданий  для общественного пользования. Электронная библиотечная система является средством управления хранения книг и процессом получения доступа к ним.

## Краткий анализ аналогичных решений по 3 критериям

| ЭБС        | Возможность использования в библиотеках | Возможность разнообразной фильтрации | Возможность использования большой аудиторией | Онлайн-доступ к книгам |
| ------------- | ------------- | ------------- | ------------- |------------- |
| Лань     | - | + | + | + |
| Московская ЭБС | +| -| - | - |
| eLibrary | - | - | + | + |

## Краткое обоснование целесообразности и актуальности проекта

В сети есть достаточно много ресурсов, позволяющих получить доступ к книгам в электронном виде. Такие сервисы предлагают возможность разнообразной фильтрации, однако они могут быть использованы исключительно в онлайн-режиме. Возможность интеграции в реальные библиотеки они не предусматривают. С другой стороны, во многих городах России есть системы, позволяющие записаться в библиотеки города или посмотреть наличие книг в них. Недостатком таких систем является то, что они не предоставляют возможности гибко фильтровать книги и то, что в разных городах (а иногда и в разных сетях библиотек города) системы разные. Именно пожтому предлагается создать систему, объединяющую в себе достоинства существующих решений и учитывающую их недостатки.

## Use-Case - диаграмма

![use-case drawio](https://user-images.githubusercontent.com/55718346/162726609-a464c58a-830e-4ae6-a5a7-23e424ee4e4b.png)


## ER-диаграмма сущностей

![er drawio](https://user-images.githubusercontent.com/55718346/162637672-0bfa50b1-179b-4672-9728-92ad85b2a0e0.png)

## Архитектурные характеристики, важные для проекта

- система должна обеспечивать возможность одновременной работы нескольких пользователей (читателей, администратора, библиотекарей);
- система должна быть гибкой в отношении появления новых способов фильтрации.


## Описание типа приложения и выбранного технологического стека

**Тип приложения:** Desktop

**Технологический стек:**
- С++ - используемый язык;
- QT - интерфейс;
- SOCI - библиотека для доступа к БД;
- Postgres - БД;
- oat++ - библиотека для реализации сервера.

## Верхнеуровневое разбиение на компоненты

Выделяются следующие компоненты:
- компонент доступа к данным;
- компонент бизнес-логики;
- компонент реализации UI. 

## UML диаграммы классов для двух отдельных компонентов.

### Доступ к данным

![DBAccess drawio](https://user-images.githubusercontent.com/55718346/162639533-66dba828-ea98-4ef3-9917-298d147f49cb.png)

### Компонент с бизнес-логикой


