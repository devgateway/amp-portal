<?php

/**
 * Reserve a set of IDs for "system" users.
 */

// We need to rollback in case of erros (ex: nextval/setval exist only on PostgreSQL).
$transaction = db_transaction();

try {
  $table = 'users';
  $column = 'uid';

  // Create the primary key.
  $field_def = array(
    'type' => 'serial',
    'unsigned' => TRUE,
    'not null' => TRUE,
    'description' => 'Primary Key: Unique user ID.',
  );
  db_change_field($table, $column, $column, $field_def);

  // Get the connection object for the default database.
  $dbconnection = Database::getConnection();

  // Get the sequence name (including table prefix if any)
  $table = 'users';
  $column = 'uid';
  $sequence_name = $dbconnection->makeSequenceName($table, $column);

  // Get the next id for users.uid.
  $next_id = $dbconnection->query("SELECT nextval('" . $sequence_name . "')")->fetchField();

  // Make sure we don't break the next insert.
  if ($next_id < 100) {
    $next_id = $dbconnection->query("SELECT setval('" . $sequence_name . "', 100)")->fetchField();
  }
}
catch (Exception $e) {
  $transaction->rollback();
}
