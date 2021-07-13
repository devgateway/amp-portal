export const buildDonorScoreCardOptions = (donorScoreCardData) => {

  return {
    "values": [{
      "id": 3,
      "value": donorScoreCardData.noUpdates,
      "index": 2
    }, {
      "id": 2,
      "value": donorScoreCardData.late,
      "index": 1
    },
      {
        "id": 1,
        "value": donorScoreCardData.onTime,
        "index": 0
      }]
  }
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
const noDataFilter = (c) => c.value != 'No Data'
export const buildPieOptions = (data, includeTotal) => {
  if (data && data.children) {
    const values = []
    let row;
    data.children.filter(noDataFilter)
      .forEach(d => {
        //first level example gender

        d.children.filter(noDataFilter).forEach(d1 => {
          //second level
          row = {}
          if (d1.children) {


            row.id = d.value + ' - ' + d1.value //Male /African ect (dimension value)
            row.parent = d.value
            row.child = d1.value

            row.label = d.value + ' - ' + d1.value  //Male /African ect (dimension value)
            d1.children.filter(c => c.value === true).forEach(d2 => {
              row.value = (d2.sum / d1.sum) * 100
            })
          } else {
            row = {}
            //no next level thi is smoke
            row.id = d.value //Male - fmale
            row.label = d.value //Male - fmale
            row.parent = d.value
            row.child = d.value
            if (d1.value == true) {
              row.value = (d1.sum / d.sum) * 100
            }
          }
          values.push(row)

        })


      })


    return {
      data: values.sort((d1, d2) => d2.value - d1.value)
    }
  }

}
export const buildDivergingOptions = (data, includeTotal) => {
  const options = buildBarOptions(data, false)
  if (options) {
    const keys = options.keys;
    const divergingData = options.data.map(d => {
      d[keys[0]] = d[keys[0]] * -1
      d[keys[1]] = d[keys[1]]
      return d
    })
    return { ...options, data: divergingData }
  } else {
    return null;
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