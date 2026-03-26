function Product({name, price}){
    return(
        <>
            <ul>
                <li>상품명: {name} / 가격: {price}원</li>
            </ul>
        </>
    );
}

export default Product;