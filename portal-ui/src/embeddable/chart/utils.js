import React from 'react';
import { format } from 'd3-format';

export const lightenDarkenColor = (col, amt) => {

  let usePound = false;

  if (col[0] === "#") {
    col = col.slice(1);
    usePound = true;
  }

  var num = parseInt(col, 16);

  var r = (num >> 16) + amt;

  if (r > 255) r = 255;
  else if (r < 0) r = 0;

  var b = ((num >> 8) & 0x00FF) + amt;

  if (b > 255) b = 255;
  else if (b < 0) b = 0;

  var g = (num & 0x0000FF) + amt;

  if (g > 255) g = 255;
  else if (g < 0) g = 0;

  return (usePound ? "#" : "") + (g | (b << 8) | (r << 16)).toString(16);

}

export const getTextWidth = (text, font) => {
  // re-use canvas object for better performance
  var canvas = getTextWidth.canvas || (getTextWidth.canvas = document.createElement("canvas"));
  var context = canvas.getContext("2d");
  context.font = font;
  var metrics = context.measureText(text);
  return metrics.width;
}

export function formatKMB(intl, precision, decimalSeparator, summary, lang) {
  const formatSI = format(`.${precision || 3}s`);
  decimalSeparator = decimalSeparator || '.';
  if (summary) {
    return (value) => formatSI(value)
      .replace('k', getSuffixForLang('k', lang))
      .replace('G', getSuffixForLang('G', lang))
      .replace('.', decimalSeparator);
  }
  return (value) => formatSI(value)
    .replace('k', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-thousand', defaultMessage: "k" })}`)
    .replace('M', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-million', defaultMessage: "M" })}`)
    .replace('G', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-billion', defaultMessage: "B" })}`)
    .replace('T', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-trillion', defaultMessage: "T" })}`)
    .replace('P', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-peta', defaultMessage: "P" })}`)
    .replace('E', ` ${intl.formatMessage({ id: 'amp.dashboard:chart-exa', defaultMessage: "E" })}`)
    .replace('.', decimalSeparator);
}

const getSuffixForLang = (prefix, lang) => {
  // eslint-disable-next-line default-case
  switch (lang) {
    case 'en':
      return prefix;
    case 'fr':
      // eslint-disable-next-line default-case
      switch (prefix) {
        case 'k':
          return 'm';
        case 'G':
          return 'MM';
      }
      break;
    case 'sp':
      // eslint-disable-next-line default-case
      switch (prefix) {
        case 'G':
          return 'B';
      }
      break;
  }
  return prefix;
}

export const formatNumber = (currency, intl, value, precision, decimalSeparator, groupSeparator, numberDivider,
                             numberDividerDescriptionKey) => {
  const formatString = `,${precision >= 0 ? `.${precision}` : ''}f`;
  const dividedValue = (numberDivider && numberDividerDescriptionKey) ? value / numberDivider : value;
  // eslint-disable-next-line max-len
  const txtVal =
    <b>{format(formatString)(dividedValue).replace(/[,]+/g, groupSeparator).replace(/[.]+/g, decimalSeparator)}</b>;
  return (
    <>
      {txtVal}
      {' '}
      {currency}
      {numberDivider && numberDividerDescriptionKey
        ? ` (${intl[`amp.ndd.dashboard:${numberDividerDescriptionKey}`]})`
        : null}
    </>
  );
}

export const formatNumberWithSettings = (currency, intl, settings, value, useUnits) => {
  if (useUnits) {
    return formatNumber(currency, intl, value, settings.precision, settings.decimalSeparator,
      settings.groupSeparator, settings.numberDivider, settings.numberDividerDescriptionKey);
  }
  return formatNumber(currency, intl, value, settings.precision, settings.decimalSeparator,
    settings.groupSeparator);
}
export const getGlobalSettings = (settings) => {
  const globalSettings = {};

  globalSettings.numberglobalSettings = settings['number-globalSettings'] || '#,#.#';
  globalSettings.precision = 0;
  if (globalSettings.numberglobalSettings.indexOf('.') !== -1) {
    globalSettings.precision = globalSettings.numberglobalSettings.length - globalSettings.numberglobalSettings.indexOf('.') - 1;
  }
  if (globalSettings.numberglobalSettings.indexOf(',') !== -1) {
    globalSettings.groupSeparator = settings['number-group-separator'] || ',';
  } else {
    globalSettings.groupSeparator = '';
  }
  globalSettings.decimalSeparator = settings['number-decimal-separator'] || '.';
  globalSettings.numberDivider = settings['number-divider'];
  if (globalSettings.numberDivider === 1) {
    globalSettings.numberDividerDescriptionKey = 'inunits';
  } else if (globalSettings.numberDivider === 1000) {
    globalSettings.numberDividerDescriptionKey = 'inthousands';
  } else if (globalSettings.numberDivider === 1000000) {
    globalSettings.numberDividerDescriptionKey = 'inmillions';
  } else if (globalSettings.numberDivider === 1000000000) {
    globalSettings.numberDividerDescriptionKey = 'inbillions';
  }

  globalSettings.dateglobalSettings = settings['default-date-globalSettings'];
  globalSettings.defaultMinDate = settings['dashboard-default-min-date'];
  globalSettings.defaultMaxDate = settings['dashboard-default-max-date'];
  return globalSettings;
}

