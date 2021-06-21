import { __ } from '@wordpress/i18n';
import { registerBlockType } from '@wordpress/blocks';
import BlockSave from "./BlockSave";
import BlockEdit from "./BlockEdit";
import { Map } from '../../icons'

registerBlockType('dg-components/map',
  {
    title: __('Dg Map', 'dg-components'),
    icon: Map,
    category: 'react-blocks',
    apiVersion: 2,
    attributes: {
      height: {
        type: 'number',
        default: 500,
      },

      baseMap: {
        type: 'string',
        default: "openStreetMaps",
      },
      adminLevel: {
        type: 'string',
        default: 'adm-1'
      },
      viewMoreLink: {
        type: 'string',
        dafault: 'https://www.developmentgateway.org'
      },
      viewMorePosition: {
        type: 'string',
        default: 'bottomleft'
      },
      zoomLevel: {
        type: 'number',
        default: 8
      },
      zoomTextIn: {
        type: 'string',
        default: 'Zoom in'
      },
      zoomTextOut: {
        type: 'string',
        default: 'Zoom out'
      },
      resetText: {
        type: 'string',
        default: 'Reset text'
      },
      centerText: {
        type: 'string',
        default: 'centerText'
      }

    }
    ,
    edit: BlockEdit,
    save: BlockSave,
  }
)
;
