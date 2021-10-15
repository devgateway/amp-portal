/* eslint-disable react/react-in-jsx-scope */
import { TextControl, CheckboxControl, PanelBody, PanelRow, SelectControl } from '@wordpress/components';
import { __ } from '@wordpress/i18n';
import { useEffect } from "react";


const FundingConfiguration = ({ app, fundingType, setAttributes, keys, yearFilter }) => {

  const fundingTypeConfiguration = [
    { value: "ftype", label: 'Funding Type' },
    { value: "finstrument", label: 'Financing Instrument' },


  ]
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
    </PanelBody>

  )

}

export default FundingConfiguration