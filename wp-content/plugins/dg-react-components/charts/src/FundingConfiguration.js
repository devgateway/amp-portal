/* eslint-disable react/react-in-jsx-scope */
import { TextControl, CheckboxControl, PanelBody, PanelRow, SelectControl } from '@wordpress/components';
import { __ } from '@wordpress/i18n';
import { useEffect } from "react";


const FundingConfiguration = ({ app, fundingType, setAttributes, keys, yearFilter }) => {

  const fundingTypeConfiguration = [
    { value: "ftype", label: 'Funding Type' },
    { value: "finstrument", label: 'Financing Instrument' },


  ]


  const onKeyChange = (value) => {
    if (keys.indexOf(value) > -1) {
      setAttributes({ keys: keys.filter(d => d != value) })
    } else {
      setAttributes({ keys: [...keys, value] })
    }
  }

  return (
    <PanelBody initialOpen={false} title={__("Funding Configuration")}>

      <PanelRow>
        <SelectControl
          label={__('fundingType')}
          value={[fundingType]} // e.g: value = [ 'a', 'c' ]
          onChange={(value) => {
            setAttributes({ fundingType: value })
          }}
          options={fundingTypeConfiguration}
        />
      </PanelRow>
      <PanelRow>
        <CheckboxControl
          label={__("Official Consumption")}
          checked={keys.indexOf("consumption") > -1}
          onChange={e => onKeyChange("consumption")
          }
        />
      </PanelRow>
      <PanelRow>
        <CheckboxControl
          label={__("Total Consumption")}
          checked={keys.indexOf("total") > -1}
          onChange={e => onKeyChange("total")
          }
        />
      </PanelRow>
      <PanelRow>
        <CheckboxControl
          label={__("Excise rate")}
          checked={keys.indexOf("rate") > -1}
          onChange={e => onKeyChange("rate")}
        />
      </PanelRow>
      <PanelRow>
        <CheckboxControl
          label={__("Retail Price")}
          checked={keys.indexOf("price") > -1}
          onChange={e => onKeyChange("price")}
        />
      </PanelRow>

      <PanelRow>
        <TextControl
          label={__("Year Filter")}
          value={yearFilter}
          onChange={(yearFilter) => setAttributes({ yearFilter })}
        />
      </PanelRow>
    </PanelBody>

  )

}

export default FundingConfiguration