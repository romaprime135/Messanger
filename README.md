# Messanger project

## Проект делался только мной, поэтому списка участников конечно не будет и ясно, что все реализовывал я
## Как дополнительный функционал я реализовал маркировки важности сообщений (Low, Medium, High)
## Мной были реализованы классы User(Username, Password, Name) и message(Getter, Sender, Text, Tag)
## Для запоминания сообщений и пользователей я решил сделать их сохранение в файлы messages.txt и users.txt соответственно
## Все действия программы я перенес в функции (registerUser(), loginUser(), sendToAll(User*), sendPrivate(User*), viewMessages(User*), chatMenu(User*))
## В классах создал геттеры и методы чтения/записи данных (getMessage(const char*), addMessage(const char*, message), saveUser(const User&), loadUsers(), userExists(const std::string&))
