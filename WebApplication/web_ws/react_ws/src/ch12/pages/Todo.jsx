import { useParams } from "react-router-dom";
import { Link } from "react-router-dom";

export default function Todo({todo}) {

    const {id} = useParams();
    const currentTodo = todo.find((item) => String(item.id) === id);

    if (!currentTodo) {
        return (
            <div>
                <div>해당 Todo를 찾을 수 없습니다.</div>
                <Link to={'/'} className="back-link">홈으로 돌아가기</Link>
            </div>
        );
    }

    return(
        <div>
            <div>Todo 페이지입니다.</div>
            <div>{id}번째 할일</div>
            {currentTodo.isDone
            ?<div>- 상태: 완료</div>
            :<div>- 상태: 미완료</div>}
            <div>- 내용: {currentTodo.content}</div>
            <div>- 생성일: {new Date(currentTodo.createdDate).toLocaleString("ko-KR")}</div>
            <Link to={'/'} className="back-link">홈으로 돌아가기</Link>
        </div>
    );
}
