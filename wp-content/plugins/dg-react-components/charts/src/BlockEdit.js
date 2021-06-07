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
  ToggleControl
} from '@wordpress/components';

import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
import { __ } from '@wordpress/i18n';
import { Button as Btn, Grid } from 'semantic-ui-react'
import { SizeConfig } from '../../commons/index'
import TopConfiguration from './TopConfiguration'
import FundingConfiguration from "./FundingConfiguration";

class BlockEdit extends Component {


  constructor(props) {
    super(props);
    this.colors = [
      { value: "nivo", label: 'nivo' },
      { value: "category10", label: 'category10' },
      { value: "accent", label: 'None' },
      { value: "dark2", label: 'dark2' },
      { value: "paired", label: 'paired' },
      { value: "pastel1", label: 'pastel1' },
      { value: "pastel2", label: 'pastel2' },
      { value: "set1", label: 'set1' },
      { value: "set2", label: 'set2' },
      { value: "set3", label: 'set3' },
      { value: "blues", label: 'blues' },
      { value: "greens", label: 'greens' },
      { value: "greys", label: 'greys' },
      { value: "oranges", label: 'oranges' },
      { value: "purples", label: 'purples' },
      { value: "reds", label: 'reds' },
      { value: "blue_green", label: 'blue_green' },
      { value: "blue_purple", label: 'blue_purple' },
      { value: "green_blue", label: 'green_blue' },
      { value: "orange_red", label: 'orange_red' },
      { value: "purple_blue_green", label: 'purple_blue_green' },
      { value: "purple_blue", label: 'purple_blue' },
      { value: "purple_red", label: 'purple_red' },
      { value: "red_purple", label: 'red_purple' },
      { value: "yellow_green_blue", label: 'yellow_green_blue' },
      { value: "yellow_green", label: 'yellow_green' },
      { value: "yellow_orange_brown", label: 'yellow_orange_brown' },
      { value: "yellow_orange_red", label: 'yellow_orange_brown' },
      { value: "amp_dashboards", label: 'amp_dashboards' }
    ];
    this.measures = [
      { value: 'Actual Commitments', label: 'Actual Commitments' },
      { value: 'Actual Disbursements', label: 'Actual Disbursements' },
      { value: 'Actual Expenditures', label: 'Actual Expenditures' },
    ]


  }

  componentDidUpdate(prevProps, prevState, snapshot) {
    const {
      setAttributes,
      attributes: {},
    } = this.props;

    if (prevProps.attributes) {
    }

  }

  componentDidMount() {
    const {
      setAttributes,
      isSelected,
      attributes: {
        height,
        type,
        source,
        bottom,
        left,
        scheme,
        colorBy
      }
    } = this.props;

  }

  onSelect() {

  }

  render() {
    const {
      className, isSelected,
      toggleSelection, setAttributes, attributes: {
        height,
        type,
        groupMode,
        bottomLegend,
        leftLegend,
        scheme,
        colorBy,
        topChartType,
        topChartColumnCount,
        fundingType,
        mode,
        dualMode,
        toggleInfoLabel,
        toggleChartLabel,
        chartTitle,
        dataSource,
        showLegends,
        legendPosition,
        legendsWidth,
        app,
        measure,
        dateFrom,
        dateTo,
        keys,
        tickColor,
        tickRotation,
        formatStyle,
        decimalPoints,
        currency,
        yearFilter,

      }
    } = this.props;

    const levels = app == 'top' ? [topChartType, topChartColumnCount,] : [fundingType];
    const source = levels.filter(l => l != 'none' && l != null).join('/')

    let params = {}
    if (yearFilter != null && yearFilter.trim() !== "" && app === 'policy') {
      const year = yearFilter.split(",").map(d => parseInt(d))
      params["year"] = year
    }

    let queryString = `data-editing=true&data-style=${formatStyle}&data-decimals=${decimalPoints}&data-currency=${currency}&data-params=${encodeURIComponent(JSON.stringify(params))}${tickColor != null ? `&data-tick-color=${tickColor}` : ""}&data-tick-rotation=${tickRotation}&data-keys=${keys.join(',')}&data-app=${app}&data-height=${height}&data-chart-type=${type}&data-source=${source}&data-color-by=${colorBy}&data-color-scheme=${scheme}&data-group-mode=${groupMode}&data-legends-left=${leftLegend}&data-legends-bottom=${bottomLegend}&data-dualmode=${dualMode}&editing=true&data-legend-position=${legendPosition}&data-edit-mode=${mode}&data-legends-width=${legendsWidth}&data-show-legends=${showLegends}&data-toggle-info-label=${toggleInfoLabel}&data-toggle-chart-label=${toggleChartLabel}&data-chart-title=${chartTitle}&data-chart-data-source=${dataSource}`
    queryString += `&data-chart-measure=${measure}&data-chart-date-from=${dateFrom}&data-chart-date-to=${dateTo}`;
    const divStyles = { height: height - 85 + 'px', width: '100%' }
    return ([isSelected && (
        <InspectorControls>
          <Panel header={__("Chart Configuration")}>
            <PanelBody initialOpen={false} title={__("Info Graphic")}>
              <PanelRow>
                <ToggleControl
                  label="Use Infographic"
                  checked={dualMode}
                  onChange={(dualMode) => setAttributes({ dualMode, mode: 'chart' })}
                />
              </PanelRow>
            </PanelBody>
            {dualMode && <PanelBody initialOpen={false} title={__("View Mode")}>
              <PanelRow>
                <ToggleControl
                  label="Infographic"
                  checked={mode == 'info'}
                  onChange={() => setAttributes({ mode: (mode == 'chart' ? 'info' : 'chart') })}
                />
              </PanelRow>
            </PanelBody>
            }

            {dualMode && <PanelBody initialOpen={false} title={__("Toggle Labels")}>
              <PanelRow>
                <TextControl
                  label={__('Toggle Info Graphic Label')}
                  value={toggleInfoLabel}
                  onChange={(toggleInfoLabel) => setAttributes({ toggleInfoLabel })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('Toggle Chart Label')}
                  value={toggleChartLabel}
                  onChange={(toggleChartLabel) => setAttributes({ toggleChartLabel })}
                />
              </PanelRow>
            </PanelBody>}
            <SizeConfig initialOpen={false} setAttributes={setAttributes} height={height}></SizeConfig>
            <PanelBody initialOpen={false} title={__("API & Source")}>
              <PanelRow>
                <SelectControl
                  value={[app]} // e.g: value = [ 'a', 'c' ]
                  onChange={(app) => {
                    setAttributes({ app })
                  }}
                  options={[
                    { label: 'Top', value: 'top' },
                    { label: 'Funding', value: 'funding' },
                    { label: 'Donor scorecard', value: 'donorScoreCard' },
                    { label: 'Top List', value: 'topList' },
                    { label: 'Login', value: 'login' },
                    { label: 'Total Widget', value: 'totalWidget' }
                  ]}
                />
              </PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('Funding measure')}
                  value={[measure]} // e.g: value = [ 'a', 'c' ]
                  onChange={(measure) => {
                    setAttributes({ measure })
                  }}
                  options={this.measures}
                />
              </PanelRow>
              <PanelRow>
                <RangeControl
                  label={__('Date from')}
                  value={dateFrom}
                  onChange={(dateFrom) => setAttributes({ dateFrom })}
                  min={2000}
                  max={2030}
                />
              </PanelRow>
              <PanelRow>
                <RangeControl
                  label={__('Date To')}
                  value={dateTo}
                  onChange={(dateTo) => setAttributes({ dateTo })}
                  min={2000}
                  max={2030}
                />
              </PanelRow>


            </PanelBody>


            {app == 'top' &&
            <TopConfiguration
              setAttributes={setAttributes}
              topChartType={topChartType}
              topChartColumnCount={topChartColumnCount}
            >
            </TopConfiguration>}
            {app == 'funding' &&
            <FundingConfiguration
              yearFilter={yearFilter}
              keys={keys}
              setAttributes={setAttributes}
              fundingType={fundingType}>
            </FundingConfiguration>}


            <PanelBody initialOpen={false} title={__("Chart Type")}>
              <PanelRow>
                <SelectControl
                  label={__('Type')}
                  value={[type]} // e.g: value = [ 'a', 'c' ]
                  onChange={(value) => {
                    setAttributes({ type: value })
                  }}
                  options={[
                    { label: 'Bar', value: 'bar' },
                    { label: 'Half Pie', value: 'halfPie' },
                    { label: 'Line', value: 'line' }]}
                />

              </PanelRow>
              <PanelRow>
                <SelectControl
                  label={__('Group Mode')}
                  value={[groupMode]} // e.g: value = [ 'a', 'c' ]
                  onChange={(value) => {
                    setAttributes({ groupMode: value })
                  }}
                  options={[{ label: 'Stacked', value: 'stacked' }, {
                    label: 'Grouped', value: 'grouped'
                  }]}
                />
              </PanelRow>

            </PanelBody>
            <PanelBody initialOpen={false} title={__("Colors")}>
              {type != 'line' && <PanelRow>
                <SelectControl
                  label={__('Color By')}
                  value={[colorBy]} // e.g: value = [ 'a', 'c' ]
                  onChange={(value) => {
                    setAttributes({ colorBy: value })
                  }}
                  options={[{ label: 'Index', value: 'index' }, { label: 'Keys', value: 'id' }]}
                />
              </PanelRow>}
              <PanelRow>
                <SelectControl
                  label={__('Color Scheme')}
                  value={[scheme]} // e.g: value = [ 'a', 'c' ]
                  onChange={(value) => {
                    setAttributes({ scheme: value })
                  }}
                  options={this.colors}
                />
              </PanelRow>
            </PanelBody>


            <PanelBody initialOpen={false} title={__("Format")}>
              <PanelRow>
                <SelectControl
                  label={__('Style')}
                  value={[formatStyle]} // e.g: value = [ 'a', 'c' ]
                  onChange={(value) => {
                    setAttributes({ formatStyle: value })
                  }}
                  options={[
                    { label: 'Decimal', value: 'decimal' },
                    { label: 'Currency', value: 'currency' },
                    { label: 'Percent', value: 'percent' }
                  ]
                  }
                />
              </PanelRow>

              <PanelRow>
                <TextControl
                  label={__("Decimal Points")}
                  onChange={decimalPoints => setAttributes({ decimalPoints })}
                  value={decimalPoints}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__("Currency")}
                  onChange={currency => setAttributes({ currency })}
                  value={currency}
                />
              </PanelRow>
            </PanelBody>

            <PanelBody initialOpen={false} title={__("Legends")}>
              <PanelRow>
                <ToggleControl
                  label={__("Show Legends")}
                  checked={showLegends}
                  onChange={() => setAttributes({ showLegends: !showLegends })}
                />
              </PanelRow>
              {showLegends && <PanelRow>
                <ButtonGroup>
                  <Button isPrimary={legendPosition == 'left'} isSecondary={legendPosition != 'left'}
                          onClick={e => setAttributes({ legendPosition: "left" })}>
                    Left
                  </Button>
                  <Button isPrimary={legendPosition == 'right'}
                          isSecondary={legendPosition != 'right'}
                          onClick={e => setAttributes({ legendPosition: "right" })}>
                    Right
                  </Button>
                  <Button isPrimary={legendPosition == 'bottom'}
                          isSecondary={legendPosition != 'bottom'}
                          onClick={e => setAttributes({ legendPosition: "bottom" })}>
                    Bottom
                  </Button>
                </ButtonGroup>
              </PanelRow>}
              {showLegends && <PanelRow>
                <RangeControl
                  label={__('Legends Width')}
                  value={legendsWidth}
                  onChange={(legendsWidth) => setAttributes({ legendsWidth })}
                  min={1}
                  max={500}
                />
              </PanelRow>}
            </PanelBody>
            <PanelBody initialOpen={false} title={"Tick Config"}>
              <PanelRow>
                <AnglePickerControl value={tickRotation}
                                    onChange={value => setAttributes({ tickRotation: value })} />
              </PanelRow>
              {(colorBy == 'id' || type == 'line') && <PanelRow>
                <PanelColorSettings
                  title={__('Color settings')}
                  colorSettings={[
                    {
                      value: decodeURIComponent(tickColor),
                      onChange: (color) => {
                        if (color) {
                          setAttributes({ tickColor: encodeURIComponent(color) })
                        } else {
                          setAttributes({ tickColor: null })
                        }
                      },
                      label: __('Tick color')
                    },
                  ]}
                />
              </PanelRow>}

            </PanelBody>
            <PanelBody initialOpen={false} title={__("Labels")}>
              <PanelRow>
                <TextControl
                  label={__('Y Axis Label')}
                  value={leftLegend}
                  onChange={(leftLegend) => setAttributes({ leftLegend })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('X axis Label')}
                  value={bottomLegend}
                  onChange={(bottomLegend) => setAttributes({ bottomLegend })}
                />
              </PanelRow>


              <PanelRow>
                <TextControl
                  label={__('Chart title')}
                  value={chartTitle}
                  onChange={(chartTitle) => setAttributes({ chartTitle })}
                />
              </PanelRow>
              <PanelRow>
                <TextControl
                  label={__('DataSource')}
                  value={dataSource}
                  onChange={(dataSource) => setAttributes({ dataSource })}
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
              {mode == "chart" && <iframe scrolling={"no"} style={divStyles}
                                          src={process.env.EMBEDDABLE_URI + "/chart?" + queryString} />}
              {mode == "info" && <div><InnerBlocks /></div>}

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


