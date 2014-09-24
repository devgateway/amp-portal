<?php

/**
 * @file
 * Display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 */
?>

<div class="page-wrapper">
  <header role="banner" class="main-header">
    <div class="main-header-inner clearfix">
      <h1 class="site-name">
        <?php print theme('header_logo'); ?>
      </h1>
      <?php print theme('header_items'); ?>
    </div>
  </header>

  <nav role="navigation" class="main-navigation">
    <div class="navigation-toplevel">
      <?php print theme('main_navigation'); ?>
    </div>
  </nav>

  <section role="main" id="main-content" class="main-content clearfix<?php print $main_content_classes; ?>">
    <div class="main-content-inner">
      <?php print render($browser_warnings); ?>

      <?php if ($title): ?>
        <div class="page-title-wrapper">
          <?php print render($title_prefix); ?>
          <h1 class="page-title"><?php print $title; ?></h1>
          <?php print render($title_suffix); ?>
          <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if ($breadcrumb && $display_breadcrumb): ?>
        <div class="breadcrumb-wrapper"><?php print $breadcrumb; ?></div>
      <?php endif; ?>

      <?php if (!empty($tabs['#primary']) && $display_tabs): ?>
        <div class="tabs-wrapper"><?php print render($tabs); ?></div>
      <?php endif; ?>

      <section class="messages-wrapper clearfix">
        <?php print $messages; ?>
      </section>

      <?php print render($page['help']); ?>
      <?php print render($page['content']); ?>
      <?php // print $feed_icons; ?>
    </div>
  </section>
</div>
