# Library system

**Идея проекта**

Рзработать библиотечную систему, которая позволит читателям получать информацию о доступных книгах в разных библиотеках, а библиотекарям - выдвать и принимать книги.

**Предметная область**

Библиотека - это учреждение, собирающее и осуществляющее хранение книг и иных печатных изданий  для общественного пользования. Электронная библиотечная система является средством управления хранения книг и процессом получения доступа к ним.

**Краткий анализ аналогичных решений по 3 критериям**

| ЭБС        | Возможность использования в библиотеках | Возможность разнообразной фильтрации | Возможность использования большой аудиторией | Онлайн-доступ к книгам |
| ------------- | ------------- | ------------- |
| Лань     | - | + | + | + |
| Московская ЭБС | +| -| - | - |
| eLibrary | - | - | + | + |

**Краткое обоснование целесообразности и актуальности проекта**

В сети есть достаточно много ресурсов, позволяющих получить доступ к книгам в электронном виде. Такие сервисы предлагают возможность разнообразной фильтрации, однако они могут быть использованы исключительно в онлайн-режиме. Возможность интеграции в реальные библиотеки они не предусматривают. С другой стороны, во многих городах России есть системы, позволяющие записаться в библиотеки города или посмотреть наличие книг в них. Недостатком таких систем является то, что они не предоставляют возможности гибко фильтровать книги и то, что в разных городах (а иногда и в разных сетях библиотек города) системы разные. Именно пожтому предлагается создать систему, объединяющую в себе достоинства существующих решений и учитывающую их недостатки.

**Use-Case - диаграмма**


**ER-диаграмма сущностей**


**Архитектурные характеристики, важные для проекта**

- система должна обеспечивать возможность одновременной работы нескольких пользователей (читателей, администратора, библиотекарей);
- система должна быть гибкой в отношении появления новых способов фильтрации.
