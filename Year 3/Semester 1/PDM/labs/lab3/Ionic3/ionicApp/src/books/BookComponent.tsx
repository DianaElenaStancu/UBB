import React, { memo } from "react";
import { IonItem, IonLabel, IonNote } from "@ionic/react";
import { getLogger } from "../core";
import { BookProps } from "./BookProps";
import styles from "./styles.module.css";

interface BookPropsExtended extends BookProps {
    onEdit: (_id?: string) => void;
}
const photoStyle = { width: '30%', margin: "0 0 0 35%" };

const BookComponent: React.FC<BookPropsExtended> = ({_id, title, launchDate, publisher, lastVersion, url, authors, totalReleases, isRead, isNotSaved, webViewPath, onEdit }) => (  
    <IonItem style={{color:isNotSaved?"red":undefined, height:"20vw"}} onClick={() => onEdit(_id)}>
      <IonNote style={{"width":"5vw"}}>{publisher}</IonNote>
      <IonLabel><b>{title}</b> V <i>{lastVersion}</i> by <i>{authors.join(", ")}</i></IonLabel>      
      <br/>
      <IonLabel>launched on {launchDate ? new Date(launchDate).toISOString().split("T")[0] : "(Invalid date)"} {isRead ? "(already read)" : ""}</IonLabel>      
      {webViewPath && (<img style={photoStyle} src={webViewPath} width={'200px'} height={'200px'}/>)}
    </IonItem>
);

export default memo(BookComponent);
