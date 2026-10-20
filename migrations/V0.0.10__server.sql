CREATE TABLE server (
    id         BIGINT      PRIMARY KEY AUTOINCREMENT,
    name       VARCHAR(50) NOT NULL,
    servername VARCHAR(50) DEFAULT NULL,
    avatar     TEXT        DEFAULT NULL,
);
