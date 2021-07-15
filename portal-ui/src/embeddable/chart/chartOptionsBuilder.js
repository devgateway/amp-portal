export const buildDonorScoreCardOptions = (donorScoreCardData) => {
  return {
    values: [
      {
        id: "amp.on-time",
        one: donorScoreCardData.onTime,
        two: 100 - donorScoreCardData.onTime,
        index: 0
      },
      {
        id: "amp.validation",
        one: donorScoreCardData.validationPeriod,
        two: 100 - donorScoreCardData.validationPeriod,
        index: 1
      },
      {
        id: "amp.late",
        one: donorScoreCardData.late,
        two: 100 - donorScoreCardData.late,
        index: 2
      },
      {
        id: "amp.no-updates",
        one: donorScoreCardData.noUpdates,
        two: 100 - donorScoreCardData.noUpdates,
        index: 3
      }
    ]
  };
}
export const buildBarOptions = (data, includeTotal, intl) => {
  const usePercents = true
  if (data && data.values) {
    const series = []
    const vals = []
    const totalCount = data.count;
    const totalSum = data.total;
    const indexBy = 'Year';
    const keysAndLegends = new Map();
    const total = 0;
    const others = new Map();
    //calculate others
    data.values.forEach(y => {
      y.values.forEach(f => {
        const subtotal = others.get(f.id);
        others.set(f.id, (subtotal ? subtotal : 0) + f.amount);
      })
    })
    const nonOthers = Array.from((new Map([...others.entries()].sort((a, b) => b[1] - a[1]))).keys()).slice(0, 3);
    const othersLabel = intl.formatMessage({ id: 'amp.others', defaultMessage: "Others" })
    data.values.forEach(d => {
      const row = {}
      row['Year'] = d.Year
      if (d.values) {
        d.values.forEach(d1 => {
          if (nonOthers.includes(d1.id)) {
            row[d1.id] = d1.amount;
            row[`item_legend_${d1.id}`] = d1.type;
            keysAndLegends.set(d1.id, d1.type);
          } else {
            //TODO make configurable
            row[`item_legend_999999`] = othersLabel;
            keysAndLegends.set(999999, othersLabel);
            row[999999] = (row[999999] ? row[999999] : 0) + d1.amount;
          }
          vals.push(d1.amount);
        })
      }
      series.push(row)

    });
    return {
      maxValue: Math.max(...vals) + 5,
      indexBy,
      keysAndLegends: keysAndLegends,
      data: series,
      total: totalSum
    }
  } else {
    return null
  }
}


export const buildTopsData = (data) => {
  const result = {};

  result.values = data.values.slice(0, 5).map((v, index) => ({
    id: v.id.toString(),
    formattedAmount: v.amount,
    name: v.name,
    value: v.amount,
    index: index
  }));
  const others = data.total - data.values.reduce((acc, cur) => (acc + cur.amount), 0);
  if (others > 0) {
    const o = {
      id: '-9999',
      name: 'Others',
      value: others,
      formattedAmount: 99999,
      index: 5
    };
    result.values.push(o);
  }
  result.currency = data.currency;
  result.total = data.total;
  return result;
}