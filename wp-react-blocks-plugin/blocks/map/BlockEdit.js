/* eslint-disable react/react-in-jsx-scope */
import { Component } from '@wordpress/element'
import { InspectorControls, PanelColorSettings, useBlockProps } from '@wordpress/block-editor';
import {
  __experimentalNumberControl as NumberControl,
  AnglePickerControl,
  Button,
  ButtonGroup,
  Panel,
  PanelBody,
  PanelRow,
  RangeControl,
  ResizableBox,
  SelectControl,
  TextControl,
  ToggleControl,
  TextareaControl
} from '@wordpress/components';

import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
import { __ } from '@wordpress/i18n';
import { Button as Btn, Grid } from 'semantic-ui-react'
import { BaseBlockEdit, SizeConfig } from '../commons/index'

class BlockEdit extends BaseBlockEdit {


  constructor(props) {
    super(props);
    this.baseMaps = [
      { value: "openStreetMaps", label: 'openStreetMaps' },
      { value: "esriWorldTopo", label: 'esriWorldTopo' },
      { value: "openTopoMap", label: 'openTopoMap' }
    ];
    this.viewMorePositions = [
      { value: "bottomleft", label: 'Bottom Left' },
      { value: "bottomright", label: 'Bottom Right' },
      { value: "topleft", label: 'Top Left' },
      { value: "topright", label: 'Top Right' }
    ];
    this.adminLevels = adminLevelsComingFromSettings.map(c => {
      const v = {};
      v.value = c.adminLevel;
      v.label = c.title;
      return v;
    }).sort((a1, a2) => {
      if (a1.value < a2.value) {
        return -1;
      }
      if (a1.value > a2.value) {
        return 1;
      }
      return 0;
    });
  }

  render() {
    const {
      className, isSelected,
      toggleSelection, setAttributes, attributes: {
        height,
        baseMap,
        adminLevel,
        viewMoreLink,
        viewMorePosition,
        zoomLevel,
        zoomTextIn,
        zoomTextOut,
        resetText,
        centerText
      }
    } = this.props;

    let queryString = `data-height=${height}&data-base-map=${baseMap}&data-admin-level=${adminLevel}&data-view-more-link=${viewMoreLink}`;
    queryString += `&data-view-more-position=${viewMorePosition}&data-zoom-level=${zoomLevel}&data-zoom-title-out=${zoomTextOut}`;
    queryString += `&data-zoom-title-in=${zoomTextIn}&data-reset-text=${resetText}&data-center-text=${centerText}`;

    const divStyles = { height: height + 'px', width: '100%' }
    return ([isSelected && (
        <InspectorControls>
          <Panel header={__("Map Configuration")}>
            <PanelBody initialOpen={false} title={__("Map")}>
              <PanelRow>
                <SelectControl
                  label={__('Base Map')}
                  value={[baseMap]}
                  onChange={(value) => {
                    setAttributes({ baseMap: value })
                  }}
                  options={this.baseMaps}
                />
              </PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('Administrative Level')}
                  value={[adminLevel]}
                  onChange={(value) => {
                    setAttributes({ adminLevel: value })
                  }}
                  options={this.adminLevels}
                />
              </PanelRow>
            </PanelBody>
            <SizeConfig initialOpen={false} setAttributes={setAttributes} height={height}></SizeConfig>
            <PanelBody initialOpen={false} title={__("Controls configuration")}>
              <NumberControl
                isShiftStepEnabled={true}
                onChange={(zoomLevel) => setAttributes({ zoomLevel })}
                shiftStep={10}
                value={zoomLevel}
              />
              <TextControl
                label={__('Zoom in text')}
                value={zoomTextIn}
                onChange={(zoomTextIn) => setAttributes({ zoomTextIn })}
              />
              <TextControl
                label={__('Zoom out text')}
                value={zoomTextOut}
                onChange={(zoomTextOut) => setAttributes({ zoomTextOut })}
              />
              <TextControl
                label={__('Reset text')}
                value={resetText}
                onChange={(resetText) => setAttributes({ resetText })}
              />
              <TextControl
                label={__('Center text')}
                value={centerText}
                onChange={(centerText) => setAttributes({ centerText })}
              />
              <PanelRow></PanelRow></PanelBody>

            <PanelBody initialOpen={false} title={__("Labels")}>
              <PanelRow>
                <TextControl
                  label={__('View more link')}
                  value={viewMoreLink}
                  onChange={(viewMoreLink) => setAttributes({ viewMoreLink })}
                />
              </PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('View More position')}
                  value={[viewMorePosition]}
                  onChange={(viewMorePosition) => {
                    setAttributes({ viewMorePosition: viewMorePosition })
                  }}
                  options={this.viewMorePositions}
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
                      src={this.state.react_ui_url + "/en/embeddable/map?" + queryString} />

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

const adminLevelsComingFromSettings = [
  {
    "id": 123,
    "title": "Administrative Level 3",
    "adminLevel": "adm-3"
  },
  {
    "id": 77,
    "title": "Administrative Level 1",
    "adminLevel": "adm-1"
  },
  {
    "id": 76,
    "title": "Administrative Level 0",
    "adminLevel": "adm-0"
  },
  {
    "id": 119,
    "title": "Administrative Level 2",
    "adminLevel": "adm-2"
  }
]


