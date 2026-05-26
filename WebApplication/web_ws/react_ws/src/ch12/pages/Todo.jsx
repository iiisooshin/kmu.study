import { useParams } from "react-router-dom";
import { Link } from "react-router-dom";

export default function Todo({todo}) {
    
    const {id} = useParams();

    return(
        <div>
            <div>Todo 페이지입니다.</div>
            <div>{id}번째 할일</div>
            {todo[id].isDone
            ?<div>- 상태: 완료</div>
            :<div>- 상태: 미완료</div>}
            <div>- 내용: {todo[id].content}</div>
            <div>- 생성일: {new Date(todo[id].createdDate).toLocaleString("ko-KR")}</div>
            <Link to={'/'} className="back-link">홈으로 돌아가기</Link>
        </div>
    );
}
