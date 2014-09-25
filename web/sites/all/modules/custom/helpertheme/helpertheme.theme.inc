<?php

/**
 * Returns HTML for the svg icons.
 */
function theme_svg_sprite($elements) {
  if (empty($elements['symbol'])) {
    return NULL;
  }

  // Fallback SVG sprite.
  if (empty($elements['path'])) {
    $elements['path'] = drupal_get_path('module', 'helpertheme') . '/images/sprite.svg';
  }

  // Set a default attributes.
  foreach (array('height', 'width', 'viewBox') as $key) {
    if (array_key_exists($key, $elements) && is_null($elements[$key])) {
      continue;
    }

    if (!empty($elements[$key])) {
      $elements['#attributes'][$key] = $elements[$key];
      continue;
    }

    switch ($key) {
      case 'width':
      case 'height':
        $elements['#attributes'][$key] = '2em';
        break;
    }
  }

  // @TODO: improve accessibility.
  $elements['#attributes']['role'] = 'presentation';

  if (!is_null($elements['symbol'])) {
    $args = array(
      'fragment' => $elements['symbol'],
    );
  }
  $elements['#use']['xlink:href'] = url($elements['path'], $args);

  return '<svg' . drupal_attributes($elements['#attributes']) . '><use'. drupal_attributes($elements['#use']) . '/></svg>';
}

/**
 * Returns HTML for the header logo.
 */
function theme_header_logo() {
  global $theme;

  // Text for homepage header logo link.
  $site_link_title = t(variable_get('site_link_title', 'Visit the main page'));
  $site_name = filter_xss_admin(variable_get('site_name', 'Drupal'));

  $items['logo_markup'] = array(
    '#prefix' => '<a href="' . url('<front>') . '" title="' . $site_link_title . '" rel="home">',
    '#suffix' => "</a>",
  );

  // Replace the PNG logo with a SVG one.
  $items['logo_markup']['svg'] = array(
    '#theme' => 'image',
    '#path' => url(drupal_get_path('theme', $theme) . '/logo.svg'),
    '#alt' => $site_name,
    '#attributes' => array(
      'role' => 'presentation',
    ),
    '#prefix' => "<!--[if (gte IE 9)|!(IE)]><!-->",
    '#suffix' => "<!--<![endif]-->",
  );
  $items['logo_markup']['png'] = array(
    '#theme' => 'image',
    '#path' => url(drupal_get_path('theme', $theme) . '/logo.png'),
    '#alt' => $site_name,
    '#prefix' => "<!--[if lt IE 9 ]>",
    '#suffix' => "<![endif]-->",
  );

  // Render the HTML.
  return drupal_render($items);
}

/**
 * Returns HTML for the header items.
 */
function theme_header_items() {
  $menu_elements = array();

  $menu_elements = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'header-items',
      ),
    ),
  );

  $menu_elements['header'] = array(
    '#type' => 'html_tag',
    '#tag' => 'h2',
    '#value' => 'User Menu',
    '#attributes' => array('class' => array('element-invisible')),
  );

  // Get the menu links.
  $menu_name = 'user-menu';
  if ($links = helpertheme_menu_navigation_links($menu_name, 1)) {
    $menu_elements['nav']['#prefix'] = '<nav role="navigation" id="user-navigation" class="user-navigation">';
    $menu_elements['nav']['#suffix'] = '</nav>';

    $menu_elements['nav']['links'] = array(
      '#theme' => 'links__enhanced',
      '#links' => $links,
      '#links_prefix' => 'action-link',
      '#attributes' => array(
        'class' => array(
          'header-links',
          'links',
          'clearfix',
        )
      ),
    );
  }

  // Render the HTML.
  $output = drupal_render($menu_elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>\s+\</', '><', $output);
}

/**
 * Returns HTML for main navigation menu.
 */
function theme_main_navigation() {
  $menu_elements = array();

  $menu_elements['header'] = array(
    '#type' => 'html_tag',
    '#tag' => 'h2',
    '#value' => 'Main Menu',
    '#attributes' => array('class' => array('element-invisible')),
  );

  $menu_tree_callback = (function_exists('i18n_menu_translated_tree')) ? 'i18n_menu_translated_tree' : 'menu_tree';
  $menu_elements['navigation'] = $menu_tree_callback('main-menu');

  // Change the wrapper class.
  $menu_elements['navigation']['#theme_wrappers'] = array('menu_tree__main_menu__toplevel');

  // Render the menu.
  $output = render($menu_elements);

  // Remove whitespace between items. Helps with styling in-line elements.
  return preg_replace('/\>[\n\ ]+\</', '><', $output);
}
