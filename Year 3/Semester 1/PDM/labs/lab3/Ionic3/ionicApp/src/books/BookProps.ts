export interface BookProps {
    _id?: string;
    title: string;
    launchDate: Date;
    publisher:string;
    lastVersion:string;
    url:string;  
    authors:string[];
    totalReleases:number;
    isRead:boolean;
    isNotSaved?:boolean;
    latitude?:number;
    longitude?:number;
    webViewPath?: string;
}
