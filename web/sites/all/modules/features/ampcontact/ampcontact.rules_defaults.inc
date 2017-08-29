<?php
/**
 * @file
 * ampcontact.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function ampcontact_default_rules_configuration() {
  $items = array();
  $items['ampcontact_contact_form_notifications_with_subject'] = entity_import('rules_config', '{ "ampcontact_contact_form_notifications_with_subject" : {
      "LABEL" : "Contact Form Notifications (with subject)",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "AMP General" ],
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "entityform" ], "field" : "field_contact_subject" } },
        { "NOT data_is_empty" : { "data" : [ "entityform:field-contact-subject" ] } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[entityform:field-contact-email]",
            "subject" : "Contact form submission notification - [site:name]",
            "message" : "Hello [entityform:field_contact_name],\\r\\nYour data has been received.\\r\\n\\r\\nHere is a copy of the submitted data:\\r\\n[entityform:textexport-email]\\r\\n",
            "language" : [ "" ]
          }
        },
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "5" : "5" } },
            "subject" : "New contact form submission [[site:name]] - [entityform:field-contact-subject]",
            "message" : "[entityform:textexport-email]\\r\\n"
          }
        }
      ]
    }
  }');
  $items['rules_contact_form_notifications'] = entity_import('rules_config', '{ "rules_contact_form_notifications" : {
      "LABEL" : "Contact Form Notifications",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "AMP General" ],
      "REQUIRES" : [ "rules", "entityform" ],
      "ON" : { "entityform_insert" : [] },
      "IF" : [
        { "OR" : [
            { "NOT entity_has_field" : { "entity" : [ "entityform" ], "field" : "field_contact_subject" } },
            { "AND" : [
                { "entity_has_field" : { "entity" : [ "entityform" ], "field" : "field_contact_subject" } },
                { "data_is_empty" : { "data" : [ "entityform:field-contact-subject" ] } }
              ]
            }
          ]
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[entityform:field-contact-email]",
            "subject" : "Contact form submission notification - [site:name]",
            "message" : "Hello [entityform:field_contact_name],\\r\\nYour data has been received.\\r\\n\\r\\nHere is a copy of the submitted data:\\r\\n[entityform:textexport-email]\\r\\n",
            "language" : [ "" ]
          }
        },
        { "mail_to_users_of_role" : {
            "roles" : { "value" : { "5" : "5" } },
            "subject" : "New contact form submission [[site:name]]",
            "message" : "[entityform:textexport-email]\\r\\n"
          }
        }
      ]
    }
  }');
  return $items;
}
