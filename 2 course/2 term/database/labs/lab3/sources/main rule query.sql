-- CREATE ROLE "read_only_role";
-- CREATE ROLE "read_write_role";

-- GRANT SELECT ON TABLE person TO read_only_role;
-- GRANT SELECT, INSERT, UPDATE, DELETE on TABLE person TO read_write_role;

-- GRANT read_only_role TO ttsypyshev;

-- REVOKE read_only_role FROM ttsypyshev;
-- GRANT read_write_role TO ttsypyshev;

-- GRANT ALL PRIVILEGES ON TABLE person TO ttsypyshev;

ALTER USER ttsypyshev PASSWORD '4321'