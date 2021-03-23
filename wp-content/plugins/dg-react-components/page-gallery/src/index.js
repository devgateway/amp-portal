import {__} from '@wordpress/i18n';
import {registerBlockType} from '@wordpress/blocks';
import {useBlockProps, withColors} from '@wordpress/block-editor';
import {ResizableBox} from '@wordpress/components';

const EditComponent = (props) => {
    const {attributes: {width, height}, toggleSelection, setAttributes} = props;

    const urlParams = new URLSearchParams(window.location.search);
    const parent = urlParams.get('post');

    const blockProps = useBlockProps();
    const queryString = `editing=true&parent=${parent}`;
    const divClass = ""
    const divStyles = {height: height + 'px', width: width + 'px'}

    return (
        <div>
            <ResizableBox
                size={{height, width,}}
                style={{"margin": "auto"}}
                minHeight="200"
                minWidth="500"
                enable={{
                    top: false,
                    right: true,
                    bottom: true,
                    left: false,
                    topRight: false,
                    bottomRight: true,
                    bottomLeft: false,
                    topLeft: false,
                }}
                onResizeStop={(event, direction, elt, delta) => {
                    setAttributes({
                        height: parseInt(height + delta.height, 10),
                        width: parseInt(width + delta.width, 10),
                    });
                    toggleSelection(true);
                }}
                onResizeStart={() => {
                    toggleSelection(false);
                }}
            >
                <div {...blockProps} >

                    <iframe width={width}
                            height={height}
                            style={{...divStyles}} className={divClass}
                            scrolling={"no"}
                            src={process.env.EMBEDDABLE_URI + "/pagegallery?" + queryString}/>


                </div>
            </ResizableBox>
        </div>
    );
}
const SaveComponent = (props) => {
    const {} = props.attributes;
    const divClass = {}
    const divStyles = {}
    return (<div className={divClass} style={divStyles}>
            <div {...props.attributes} className={"tcdi-component"} data-component={"pageGallery"}></div>
        </div>


    );
}

registerBlockType('tcdi-components/page-gallery',
    {
        title: __('Child Pages Gallery', 'tcdi-components'),
        icon: 'images-alt2',
        category: 'tcdi-blocks',
        attributes: {
            count: {
                type: 'number',
                default: 3,
            },
            height: {
                type: "number",
                default: 400
            },
            width: {
                type: "number",
                default: 800
            }
        }
        ,
        edit: withColors('backgroundColor', {textColor: 'color'})(EditComponent),
        save: SaveComponent,
    }
)
;
