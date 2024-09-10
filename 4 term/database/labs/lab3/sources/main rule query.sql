-- Создание роли "read_only_role" с доступом только на чтение
CREATE ROLE "read_only_role";

-- Создание роли "read_write_role" с доступом на чтение и запись
CREATE ROLE "read_write_role";

-- Предоставление роли "read_only_role" права на SELECT на таблице person
GRANT SELECT ON TABLE person TO read_only_role;

-- Предоставление роли "read_write_role" прав на SELECT, INSERT, UPDATE и DELETE на таблице person
GRANT SELECT, INSERT, UPDATE, DELETE on TABLE person TO read_write_role;

-- Назначение роли "read_only_role" пользователю ttsypyshev
GRANT read_only_role TO ttsypyshev;

-- Отзыв роли "read_only_role" у пользователя ttsypyshev
REVOKE read_only_role FROM ttsypyshev;

-- Назначение роли "read_write_role" пользователю ttsypyshev
GRANT read_write_role TO ttsypyshev;

-- Предоставление пользователю ttsypyshev всех привилегий на таблицу person
GRANT ALL PRIVILEGES ON TABLE person TO ttsypyshev;

-- Изменение пароля пользователя ttsypyshev на '4321'
ALTER USER ttsypyshev PASSWORD '4321';
