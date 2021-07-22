/* eslint-disable react/react-in-jsx-scope */
import { Component } from '@wordpress/element'
import { InspectorControls, PanelColorSettings, useBlockProps, } from '@wordpress/block-editor';
import {
  __experimentalNumberControl as NumberControl,
  CheckboxControl,
  Panel,
  PanelBody,
  PanelRow,
  ResizableBox,
  SelectControl,
  TextControl,

  TextareaControl
} from '@wordpress/components';

import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
import { __ } from '@wordpress/i18n';
import { Button as Btn, Grid } from 'semantic-ui-react'
import { BaseBlockEdit, SizeConfig } from '../commons/index'

class BlockEdit extends BaseBlockEdit {


  constructor(props) {
    super(props);
    this.tops = [
      { value: "topDonors", label: 'Top Donors' },
      { value: "topProjects", label: 'Top Projects' },
      { value: "topUpdatedProjects", label: 'Top Updated Projects' }
    ];
    this.topsize = [
      { value: "top5", label: 'Top 5' },
      { value: "top10", label: 'Top 10' }
    ];
    this.topCurrencies = [
      { value: "USD", label: 'United States Dollar' },
      { value: "EUR", label: 'Euro' },
      { value: "JPY", label: 'Yen' },
      { value: "HTG", label: 'The gourde' }
    ];

  }

  componentDidMount() {
    super.componentDidMount();
    console.log(this.state.react_amp_url)
  }

  render() {
    const {
      className, isSelected,
      toggleSelection, setAttributes, attributes: {
        height,
        topType,
        topSize,
        topTitle,
        topDescription,
        topMonth,
        topCurrency,
        topShowDonorGroup,
        topTooltip
      }
    } = this.props;

    let queryString = `data-height=${height}&data-top-type=${topType}&data-top-size=${topSize}`;
    queryString += `&data-top-title=${topTitle}`;
    queryString += `&data-top-description=${topDescription}`;
    queryString += `&data-top-month=${topMonth}`;
    queryString += `&data-top-currency=${topCurrency}`;
    queryString += `&data-top-show-donor-group=${topShowDonorGroup}`;
    queryString += `&data-top-tooltip=${topTooltip}`;
    const divStyles = { height: height + 'px', width: '100%' }
    return ([isSelected && (
        <InspectorControls>
          <Panel header={__("Top List Configuration")}>
            <PanelBody initialOpen={false} title={__("Top List")}>
              <PanelRow>
                <SelectControl
                  label={__('Top List type')}
                  value={[topType]}
                  onChange={(value) => {
                    setAttributes({ topType: value })
                  }}
                  options={this.tops}
                />
              </PanelRow>
              <PanelRow>
                <CheckboxControl
                  label={__('Show Donor group?')}
                  checked={topShowDonorGroup}
                  onChange={(topShowDonorGroup) => {
                    setAttributes({ topShowDonorGroup})
                  }}
                />
              </PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('Top list size')}
                  value={[topSize]}
                  onChange={(topSize) => {
                    setAttributes({ topSize })
                  }}
                  options={this.topsize}
                />
              </PanelRow>
              <PanelRow> <NumberControl
                isShiftStepEnabled={true}
                onChange={(topMonth) => setAttributes({ topMonth })}
                shiftStep={36}
                value={topMonth}
              /></PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('Top list currency')}
                  value={[topCurrency]}
                  onChange={(topCurrency) => {
                    setAttributes({ topCurrency })
                  }}
                  options={this.topCurrencies}
                />
              </PanelRow>
            </PanelBody>
            <SizeConfig initialOpen={false} setAttributes={setAttributes} height={height}></SizeConfig>
            <PanelBody initialOpen={false} title={__("Labels")}>
              <PanelRow>
                <TextControl
                  label={__('Title')}
                  value={topTitle}
                  onChange={(topTitle) => setAttributes({ topTitle })}
                />
              </PanelRow>
              <PanelRow>
                <TextareaControl
                  label={__('Top description')}
                  value={topDescription}
                  onChange={(topDescription) => setAttributes({ topDescription })}
                />
              </PanelRow>
              <PanelRow>
              <TextControl
                label={__('Tooltip')}
                value={topTooltip}
                onChange={(topTooltip) => setAttributes({ topTooltip })}
              />
            </PanelRow>
            </PanelBody>
          </Panel>
        </InspectorControls>),
        (<ResizableBox
            size={{ height }}
            style={{ "margin": "auto", width: "100%" }}
            minHeight="50"
            minWidth="50"
            enable={{
              top: false,
              right: false,
              bottom: true,
              left: false,
              topRight: false,
              bottomRight: false,
              bottomLeft: false,
              topLeft: false,
            }}
            onResizeStop={(event, direction, elt, delta) => {
              setAttributes({
                height: parseInt(height + delta.height, 10),
              });
              toggleSelection(true);
            }}
            onResizeStart={() => {
              toggleSelection(false);
            }}
          >
            <div className={"chart container"} style={divStyles}>
              <iframe scrolling={"no"} style={divStyles}
                      src={this.state.react_ui_url + "/en/embeddable/topLists?" + queryString} />

            </div>
          </ResizableBox>
        )]
    );

  }
}


const Edit = (props) => {
  const blockProps = useBlockProps();
  return <div {...blockProps}><BlockEdit {...props} /></div>;
}
export default Edit;



