/* eslint-disable react/react-in-jsx-scope */
import { useBlockProps } from '@wordpress/block-editor';
import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
const SaveComponent = (props) => {
  const {
    toggleSelection, setAttributes, attributes: {
      height,
      width,
      type,
      groupMode,
      bottomLegend,
      leftLegend,
      scheme,
      colorBy,
      fundingType,
      topChartType,
      topChartColumnCount,
      dualMode,
      toggleInfoLabel,
      toggleChartLabel,
      chartTitle,
      chartDescription,
      legendPosition,
      legendsWidth,
      showLegends,
      app,
      keys,
      tickColor,
      tickRotation,
      formatStyle,
      decimalPoints,
      currency,
      yearFilter,
      measure,
      dateFrom,
      dateTo,
      onTime,
      onTimeTooltip,
      late,
      lateTooltip,
      validation,
      validationTooltip,
      noUpdates,
      noUpdatesTooltip,
      ampSize
    }
  } = props;
  const blockProps = useBlockProps.save({
    className: 'tcdi component chart'
  });

  const divClass = {}
  const divStyles = {}
  const levels = app == 'top' ? [topChartType, topChartColumnCount] : [fundingType];
  let source = levels.filter(l => l != 'none' && l != null).join('/')


  let params = {}
  if (yearFilter != null && yearFilter.trim() !== "" && app === 'policy') {
    const year = yearFilter.split(",").map(d => parseInt(d))
    params["year"] = year
  }
  if (app === 'donorScoreCard') {
    source = 'donorScoreCard';
  }
  return (
    <div className={"tcdi-component"}
         data-component={"chart"}
         data-height={height}
         data-chart-type={type}
         data-source={source}
         data-color-by={colorBy}
         data-color-scheme={scheme}
         data-scheme={scheme}
         data-group-mode={groupMode}
         data-legends-left={leftLegend}
         data-dualMode={dualMode}
         data-legends-bottom={bottomLegend}
         data-toggle-info-label={toggleInfoLabel}
         data-toggle-chart-label={toggleChartLabel}

         data-chart-title={chartTitle}
         data-chart-description={chartDescription}

         data-legends-width={legendsWidth}
         data-show-legends={showLegends}
         data-legend-position={legendPosition}
         data-app={app}

         data-tick-rotation={tickRotation}
         data-tick-color={tickColor}
         data-keys={keys.join(',')}
         data-style={formatStyle}
         data-decimals={decimalPoints}
         data-currency={currency}
         data-params={encodeURIComponent(JSON.stringify(params))}
         data-chart-measure={measure}
         data-chart-date-from={dateFrom}
         data-chart-date-to={dateTo}
         data-chart-amp-on-time={onTime}
         data-chart-amp-on-time-tooltip={onTimeTooltip}
         data-chart-amp-validation={validation}
         data-chart-amp-validation-tooltip={validationTooltip}
         data-chart-amp-late={late}
         data-chart-amp-late-tooltip={lateTooltip}
         data-chart-amp-no-updates={noUpdates}
         data-chart-amp-no-updates-tooltip={noUpdatesTooltip}
         data-chart-amp-size={ampSize}
    >
      <InnerBlocks.Content />
    </div>


  );
}


export default SaveComponent