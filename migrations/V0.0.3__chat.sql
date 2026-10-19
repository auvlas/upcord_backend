CREATE TABLE chat (
    id          INTEGER  PRIMARY KEY AUTOINCREMENT,
    title       TEXT,
    chatname    TEXT,
    description TEXT,
    created_at  DATETIME DEFAULT CURRENT_TIMESTAMP
);
