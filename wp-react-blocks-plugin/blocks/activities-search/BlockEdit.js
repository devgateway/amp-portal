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
        searchTitle,
        searchTooltip,
        searchDescription,
        searchHint,
        searchButton,
        searchExtendedSlug,
        searchType
      }
    } = this.props;

    let queryString = `data-height=${height}`;
    queryString += `data-search-title=${searchTitle}`;
    queryString += `data-search-description=${searchDescription}`;
    queryString += `data-search-hint=${searchHint}`;
    queryString += `data-search-tooltip=${searchTooltip}`;
    queryString += `data-search-button=${searchButton}`;
    queryString += `data-search-type=${searchType}`;
    queryString += `data-search-extended-slug=${searchExtendedSlug}`;
    const divStyles = { height: height + 'px', width: '100%' }
    return ([isSelected && (
        <InspectorControls>
          <Panel header={__("Top List Configuration")}>
            <PanelBody initialOpen={false} title={__("API & Source")}>
              <PanelRow>
                <SelectControl
                  value={[searchType]} // e.g: value = [ 'a', 'c' ]
                  onChange={(searchType) => {
                    setAttributes({ searchType })
                  }}
                  options={[
                    { label: 'Simple Search', value: 'simpleSearch' },
                    { label: 'Extended search', value: 'extendedSearch' }
                  ]}
                />
              </PanelRow>
            </PanelBody>
            <SizeConfig initialOpen={false} setAttributes={setAttributes} height={height}></SizeConfig>
            <PanelBody initialOpen={false} title={__("Labels")}>
              <PanelRow>
                <TextControl
                  label={__('Search title')}
                  value={searchTitle}
                  onChange={(searchTitle) => setAttributes({ searchTitle })}
                />
              </PanelRow>
              <PanelRow>
                <TextareaControl
                  label={__('Search description')}
                  value={searchDescription}
                  onChange={(searchDescription) => setAttributes({ searchDescription })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('Button')}
                  value={searchButton}
                  onChange={(searchButton) => setAttributes({ searchButton })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('Hint')}
                  value={searchHint}
                  onChange={(searchHint) => setAttributes({ searchHint })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('Tooltip')}
                  value={searchTooltip}
                  onChange={(searchTooltip) => setAttributes({ searchTooltip })}
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
                      src={this.state.react_ui_url + "/en/embeddable/activitiesSearch?" + queryString} />

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



