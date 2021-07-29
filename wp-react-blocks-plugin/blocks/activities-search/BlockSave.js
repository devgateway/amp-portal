/* eslint-disable react/react-in-jsx-scope */
import { useBlockProps } from '@wordpress/block-editor';
import { InnerBlocks } from '@wordpress/editor'; // or wp.editor
const SaveComponent = (props) => {
  const {
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
      searchFiltersLocationEnabled,
      searchLocationTitle,
      searchLocationPlaceHolder,
      searchFiltersDonorEnabled,
      searchDonorTitle,
      searchDonorPlaceHolder
    }
  } = props;
  const blockProps = useBlockProps.save({
    className: 'tcdi component chart'
  });


  return (
    <div className={"tcdi-component"}
         data-component={"activitiesSearch"}
         data-height={height}
         data-search-title={searchTitle}
         data-search-description={searchDescription}
         data-search-hint={searchHint}
         data-search-tooltip={searchTooltip}
         data-search-button={searchButton}
         data-search-extended-slug={searchExtendedSlug}
         data-search-type={searchType}
         data-search-filter-primary-sector={searchFiltersPrimarySectorsEnabled}
         data-search-filter-primary-sector-title={searchPrimarySectorTitle}
         data-search-filter-primary-sector-placeholder={searchPrimarySectorPlaceHolder}
         data-search-filter-secondary-sector={searchFiltersSecondarySectorsEnabled}
         data-search-filter-secondary-sector-title={searchSecondarySectorTitle}
         data-search-filter-secondary-sector-placeholder={searchSecondarySectorPlaceHolder}
         data-search-filter-location={searchFiltersLocationEnabled}
         data-search-filter-location-title={searchLocationTitle}
         data-search-filter-location-placeholder={searchLocationPlaceHolder}
         data-search-filter-donor={searchFiltersDonorEnabled}
         data-search-filter-donor-title={searchDonorTitle}
         data-search-filter-donor-placeholder={searchDonorPlaceHolder}
    >
      <InnerBlocks.Content />
    </div>


  );
}


export default SaveComponent