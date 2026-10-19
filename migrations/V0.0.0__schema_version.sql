CREATE TABLE IF NOT EXISTS schema_version (
    version INTEGER PRIMARY KEY,
    migration_name TEXT NOT NULL,
    applied_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
