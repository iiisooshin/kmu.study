

export default function TodoItem({id, isDone, content, createdDate}) {

    return(
        <div className="TodoItem">
            <input className="checkbox_col" checked={isDone} type="checkbox" />
            <div className="title_col">{content}</div>
            <div className="date_col">{new Date(createdDate).toLocaleDateString()}</div>
            <button className="btn_col">삭제</button>
        </div>
    );
}