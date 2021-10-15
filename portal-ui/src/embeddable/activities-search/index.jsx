import React from 'react';
import DataProvider from "../data/DataProvider";
import { Container } from "semantic-ui-react";
import DataConsumer from "../data/DataConsumer";
import SearchWidget from "./SearchWidget";
import ExtendedSearchWidget from "./ExtendedSearchWidget";

const ActivitiesSearch = (props) => {
    const {
      'data-height': height = 500,
      'data-search-title': searchTitle = '',
      'data-search-description': searchDescription = '',
      'data-search-button': searchButton = 'Search',
      'data-search-hint': searchHint = '',
      'data-search-tooltip': searchTooltip,
      'data-search-extended-slug': searchExtendedSlug = 'search-results',
      'data-search-type': searchType = 'simpleSearch',
      'data-search-filter-primary-sector': searchFilterPrimarySectorB = 'true',
      'data-search-filter-primary-sector-title': searchPrimarySectorTitle = 'Primary Sector',
      'data-search-filter-primary-sector-placeholder': searchPrimarySectorPlaceHolder = 'Primary Sector',
      'data-search-filter-secondary-sector': searchFilterSecondarySectorB = 'true',
      'data-search-filter-secondary-sector-title': searchSecondarySectorTitle = 'Secondary Sector',
      'data-search-filter-secondary-sector-placeholder': searchSecondarySectorPlaceHolder = 'Secondary Sector',
      'data-search-filter-location': searchFilterLocationB = 'true',
      'data-search-filter-location-title': searchLocationTitle = 'Location',
      'data-search-filter-location-placeholder': searchLocationPlaceHolder = 'Location',
      'data-search-filter-donor': searchFilterDonorB = 'true',
      'data-search-filter-donor-title': searchDonorTitle = 'Donor Agency',
      'data-search-filter-donor-placeholder': searchDonorPlaceHolder = 'Donor Agency',
      'data-search-paging-title': pagingTitle = 'Activity Result',
      'data-search-paging-of': pagingOf = 'of',
      locale: locale = 'en',
      theParams
    }
      = props;
    const labels = {
      title: searchTitle,
      description: searchDescription,
      hint: searchHint,
      tooltip: searchTooltip,
      button: searchButton,
      pagingTitle,
      pagingOf
    };
    const filtersConfiguration = {
      primarySectorFilters: {
        enabled: searchFilterPrimarySectorB === 'true',
        title: searchPrimarySectorTitle,
        placeholder: searchPrimarySectorPlaceHolder
      },
      secondarySectorFilters: {
        enabled: searchFilterSecondarySectorB === 'true',
        title: searchSecondarySectorTitle,
        placeholder: searchSecondarySectorPlaceHolder
      },
      locationFilters: {
        enabled: searchFilterLocationB === 'true',
        title: searchLocationTitle,
        placeholder: searchLocationPlaceHolder
      },
      donorFilters: {
        enabled: searchFilterDonorB === 'true',
        title: searchDonorTitle,
        placeholder: searchDonorPlaceHolder
      }
    };

    let child;
    if (searchType === 'simpleSearch') {
      return (<Container style={{ "height": `${height}px` }} className={"body"} fluid={true}>
        <SearchWidget height={height} labels={labels} searchExtendedSlug={searchExtendedSlug} locale={locale} />
      </Container>);

    } else {
      const newSource = `activitiesSearch`;

      return <DataProvider source={newSource} app={'activitiesSearch'} store={newSource} locale={locale}
                           keyword={theParams.get('keyword')}>
        <Container style={{ "height": `${height}px` }} className={"body"} fluid={true}><DataConsumer>
          <ExtendedSearchWidget height={height} labels={labels} store={newSource}
                                filtersConfiguration={filtersConfiguration} theParams={theParams} />
        </DataConsumer></Container>
      </DataProvider>
    }
  }
;
export default ActivitiesSearch;