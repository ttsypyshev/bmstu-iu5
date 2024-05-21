# ЛР 4. Простое веб-приложение. Работа с Api

**Цель** данной лабораторной работы - взаимодействие с внешним Api через XMLHttpRequest. В ходе выполнения работы, вам предстоит ознакомиться с кодом реализации простого взаимодействия с внешним Api, получение данных и вывод их в интерфейс пользователя, и затем выполнить задания по варианту.

## План

1. Инструменты для работы
2. Что такое XMLHttpRequest
3. Работа с VK Api
4. Работа с Api
5. Api главной страницы
6. Api страницы пользователя

## Задание

Создать двухстраничное приложение из примера по вариантам.
Вариант состоит из 2 методов и доп фильтра на эти методы.

### 3 вариант

Главная страница - [messages.getConversationMembers](https://dev.vk.com/method/messages.getConversationMembers).
Получаем список участников беседы и отображаем их.
У группы можно создать чат.
Необходимо сделать несколько чатов у группы и добавить компонент для выбора `peer_id` (см. messages.getConversationMembers -> Параметры -> peer_id).

Вторая страница - [users.get](https://dev.vk.com/method/users.get).
Отображаем выбранного пользователя на первой странице.

Отображаем выбранный чат на первой странице.

## Полезные ссылки

1. Почитать про **XMLHttpRequest** [тут][xml]
2. Почитать про **VK Api** [тут][vk-api]

[vs-code]: https://code.visualstudio.com
[vs-code-live-server]: https://marketplace.visualstudio.com/items?itemName=ritwickdey.LiveServer
[node-install]: https://nodejs.org/en/download
[xml]: https://learn.javascript.ru/xmlhttprequest
[vk-api]: https://dev.vk.com/reference
[vk-api-group-key]: https://dev.vk.com/api/access-token/getting-started#Ключ%20доступа%20сообщества
[vk-api-create-group]: https://vk.com/groups?w=groups_create
[cors-unblock]: https://chrome.google.com/webstore/detail/cors-unblock/lfhmikememgdcahcdlaciloancbhjino/related