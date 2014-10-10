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
    'enabled' => 1,
    'plurals' => 3,
    'formula' => '(($n==1)?(0):((($n==0)||((($n%100)>0)&&(($n%100)<20)))?(1):2))',
    'domain' => '',
    'prefix' => 'ro',
    'weight' => 0,
  );
  return $languages;
}
