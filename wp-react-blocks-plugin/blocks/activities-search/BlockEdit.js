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
  PanelHeader,
  TextareaControl,
  Placeholder
} from '@wordpress/components';

import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
import { __ } from '@wordpress/i18n';
import { Button as Btn, Divider, Grid } from 'semantic-ui-react'
import { BaseBlockEdit, SizeConfig, FilterConfig } from '../commons/index'

class BlockEdit extends BaseBlockEdit {


  constructor(props) {
    super(props);
  }

  componentDidMount() {
    super.componentDidMount();
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
        searchType,
        searchFiltersPrimarySectorsEnabled,
        searchPrimarySectorTitle,
        searchPrimarySectorPlaceHolder,
        searchFiltersSecondarySectorsEnabled,
        searchSecondarySectorTitle,
        searchSecondarySectorPlaceHolder,
        searchFiltersDonorEnabled,
        searchDonorTitle,
        searchDonorPlaceHolder,
        searchFiltersLocationEnabled,
        searchLocationTitle,
        searchLocationPlaceHolder,
        pagingTitle,
        pagingOf
      }
    } = this.props;
    let queryString = `data-height=${height}`;
    queryString += `&data-search-title=${searchTitle}`;
    queryString += `&data-search-description=${searchDescription}`;
    queryString += `&data-search-hint=${searchHint}`;
    queryString += `&data-search-tooltip=${searchTooltip}`;
    queryString += `&data-search-button=${searchButton}`;
    queryString += `&data-search-type=${searchType}`;
    queryString += `&data-search-extended-slug=${searchExtendedSlug}`;
    queryString += `&data-search-filter-primary-sector=${searchFiltersPrimarySectorsEnabled}`;
    queryString += `&data-search-filter-primary-sector-title=${searchPrimarySectorTitle}`;
    queryString += `&data-search-filter-primary-sector-placeholder=${searchPrimarySectorPlaceHolder}`;
    queryString += `&data-search-filter-secondary-sector=${searchFiltersSecondarySectorsEnabled}`;
    queryString += `&data-search-filter-secondary-sector-title=${searchSecondarySectorTitle}`;
    queryString += `&data-search-filter-secondary-sector-placeholder=${searchSecondarySectorPlaceHolder}`;
    queryString += `&data-search-filter-location=${searchFiltersLocationEnabled}`;
    queryString += `&data-search-filter-location-title=${searchLocationTitle}`;
    queryString += `&data-search-filter-location-placeholder=${searchLocationPlaceHolder}`;
    queryString += `&data-search-filter-donor=${searchFiltersDonorEnabled}`;
    queryString += `&data-search-filter-donor-title=${searchDonorTitle}`;
    queryString += `&data-search-filter-donor-placeholder=${searchDonorPlaceHolder}`;
    queryString += `&data-search-paging-title=${pagingTitle}`;
    queryString += `&data-search-paging-of=${pagingOf}`;

    const divStyles = { height: height + 'px', width: '100%' };
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

            {searchType === 'Extended search' && <PanelBody initialOpen={false} title={__("Filters")}>
              <FilterConfig label={__("Donor Agency")} chkLabel={__("Enable Donor Agency")}
                            chkVariable={searchFiltersDonorEnabled}
                            setAttributes={setAttributes}
                            chkName="searchFiltersDonorEnabled"
                            titleLabel={__('Title')} titleVariable={searchDonorTitle}
                            titleVariableName="searchDonorTitle"
                            placeholderLabel={__('Placeholder')}
                            placeholderVariable={searchDonorPlaceHolder}
                            placeholderVariableName="searchDonorPlaceHolder"
                            setAttributes={setAttributes}
              />
              <FilterConfig label={__("Primary Sectors")} chkLabel={__("Enable Primary Sectors")}
                            chkVariable={searchFiltersPrimarySectorsEnabled}
                            setAttributes={setAttributes}
                            chkName="searchFiltersPrimarySectorsEnabled"
                            titleLabel={__('Title')} titleVariable={searchPrimarySectorTitle}
                            titleVariableName="searchPrimarySectorTitle"
                            placeholderLabel={__('Placeholder')}
                            placeholderVariable={searchPrimarySectorPlaceHolder}
                            placeholderVariableName="searchPrimarySectorPlaceHolder"
                            setAttributes={setAttributes}
              />
              <FilterConfig label={__("Secondary Sectors")} chkLabel={__("Enable Secondary Sectors")}
                            chkVariable={searchFiltersSecondarySectorsEnabled}
                            setAttributes={setAttributes}
                            chkName="searchFiltersSecondarySectorsEnabled"
                            titleLabel={__('Title')} titleVariable={searchSecondarySectorTitle}
                            titleVariableName="searchSecondarySectorTitle"
                            placeholderLabel={__('Placeholder')}
                            placeholderVariable={searchSecondarySectorPlaceHolder}
                            placeholderVariableName="searchSecondarySectorPlaceHolder"
                            setAttributes={setAttributes}
              />
              <FilterConfig label={__("Locations")} chkLabel={__("Enable Locations")}
                            chkVariable={searchFiltersLocationEnabled}
                            setAttributes={setAttributes}
                            chkName="searchFiltersLocationEnabled"
                            titleLabel={__('Title')} titleVariable={searchLocationTitle}
                            titleVariableName="searchLocationTitle"
                            placeholderLabel={__('Placeholder')}
                            placeholderVariable={searchLocationPlaceHolder}
                            placeholderVariableName="searchLocationPlaceHolder"
                            setAttributes={setAttributes}
              />
            </PanelBody>
            }
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
              <PanelRow>
                <TextControl
                  label={__('Paging title')}
                  value={pagingTitle}
                  onChange={(pagingTitle) => setAttributes({ pagingTitle })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('Paging of')}
                  value={pagingOf}
                  onChange={(pagingOf) => setAttributes({ pagingOf })}
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



