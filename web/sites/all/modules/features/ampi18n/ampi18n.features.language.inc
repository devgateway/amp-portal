<?php
/**
 * @file
 * ampi18n.features.language.inc
 */

/**
 * Implements hook_locale_default_languages().
 */
function ampi18n_locale_default_languages() {
  $languages = array();

  // Exported language: ar.
  $languages['ar'] = array(
    'language' => 'ar',
    'name' => 'Arabic',
    'native' => 'العربية',
    'direction' => 1,
    'enabled' => 0,
    'plurals' => 6,
    'formula' => '(($n==1)?(0):(($n==0)?(1):(($n==2)?(2):(((($n%100)>=3)&&(($n%100)<=10))?(3):(((($n%100)>=11)&&(($n%100)<=99))?(4):5)))))',
    'domain' => '',
    'prefix' => 'ar',
    'weight' => 0,
  );
  // Exported language: en.
  $languages['en'] = array(
    'language' => 'en',
    'name' => 'English',
    'native' => 'English',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'en',
    'weight' => 0,
  );
  // Exported language: es.
  $languages['es'] = array(
    'language' => 'es',
    'name' => 'Spanish',
    'native' => 'Español',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n!=1)',
    'domain' => '',
    'prefix' => 'es',
    'weight' => 0,
  );
  // Exported language: fr.
  $languages['fr'] = array(
    'language' => 'fr',
    'name' => 'French',
    'native' => 'Français',
    'direction' => 0,
    'enabled' => 1,
    'plurals' => 2,
    'formula' => '($n>1)',
    'domain' => '',
    'prefix' => 'fr',
    'weight' => 0,
  );
  // Exported language: ro.
  $languages['ro'] = array(
    'language' => 'ro',
    'name' => 'Romanian',
    'native' => 'Română',
    'direction' => 0,
    'enabled' => 0,
    'plurals' => 3,
    'formula' => '(($n==1)?(0):((($n==0)||((($n%100)>0)&&(($n%100)<20)))?(1):2))',
    'domain' => '',
    'prefix' => 'ro',
    'weight' => 0,
  );
  // Exported language: ru.
  $languages['ru'] = array(
    'language' => 'ru',
    'name' => 'Russian',
    'native' => 'Русский',
    'direction' => 0,
    'enabled' => 0,
    'plurals' => 3,
    'formula' => '(((($n%10)==1)&&(($n%100)!=11))?(0):((((($n%10)>=2)&&(($n%10)<=4))&&((($n%100)<10)||(($n%100)>=20)))?(1):2))',
    'domain' => '',
    'prefix' => 'ru',
    'weight' => 0,
  );
  // Exported language: sh.
  $languages['sh'] = array(
    'language' => 'sh',
    'name' => 'Serbo-Croatian',
    'native' => 'Serbo-Croatian',
    'direction' => 0,
    'enabled' => 0,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'sh',
    'weight' => 0,
  );
  // Exported language: sq.
  $languages['sq'] = array(
    'language' => 'sq',
    'name' => 'Albanian',
    'native' => 'Shqip',
    'direction' => 0,
    'enabled' => 0,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'sq',
    'weight' => 0,
  );
  // Exported language: tm.
  $languages['tm'] = array(
    'language' => 'tm',
    'name' => 'Tetum',
    'native' => 'Tetum',
    'direction' => 0,
    'enabled' => 0,
    'plurals' => 0,
    'formula' => '',
    'domain' => '',
    'prefix' => 'tm',
    'weight' => 0,
  );
  return $languages;
}
