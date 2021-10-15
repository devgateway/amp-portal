import { __ } from '@wordpress/i18n';
import { registerBlockType } from '@wordpress/blocks';
import BlockSave from "./BlockSave";
import BlockEdit from "./BlockEdit";
import { Generic } from '../icons/index'

registerBlockType(process.env.BLOCKS_NS + '/top-lists',
  {
    title: __('Top list Component'),
    icon: Generic,
    category: process.env.BLOCKS_CATEGORY,
    apiVersion: 2,
    attributes: {
      height: {
        type: 'number',
        default: 500,
      },
      topMonth: {
        type: 'number',
        default: 36,
      },
      topType: {
        type: 'string',
        default: "topDonors",
      },
      topSize: {
        type: 'string',
        default: 'top5'
      },
      topCurrency: {
        type: 'string',
        default: 'USD'
      },
      topShowDonorGroup: {
        type: 'boolean',
        default: false
      },
      topTooltip: {
        type: 'string',
        dafault: ''
      },
      topTitle: {
        type: 'string',
        dafault: 'Top 5 donors'
      },
      topDescription: {
        type: 'string',
        default: 'description'
      }

    }
    ,
    edit: BlockEdit,
    save: BlockSave,
  }
)
;
