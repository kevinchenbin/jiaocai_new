unit UnitSendMsg;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Classes, Vcl.Graphics, Vcl.Controls, Vcl.SvcMgr, Vcl.Dialogs,
  Data.DB, Data.Win.ADODB,IniFiles, Vcl.ExtCtrls, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, IdHTTP,HTTPApp;

type
  TSMService = class(TService)
    con: TADOConnection;
    query: TADOQuery;
    timer: TTimer;
    adoexe: TADOQuery;
    GetUrl: TIdHTTP;
    procedure timerTimer(Sender: TObject);
    procedure ServiceStart(Sender: TService; var Started: Boolean);
  private
    { Private declarations }
    IsSending:boolean;
  public
    function GetServiceController: TServiceController; override;
    procedure writetxt(txt:string);
    { Public declarations }
  end;

var
  SMService: TSMService;

implementation

{$R *.DFM}

procedure ServiceController(CtrlCode: DWord); stdcall;
begin
  SMService.Controller(CtrlCode);
end;

function TSMService.GetServiceController: TServiceController;
begin
  Result := ServiceController;
end;

procedure TSMService.ServiceStart(Sender: TService; var Started: Boolean);
begin
IsSending:=false;
end;

procedure TSMService.timerTimer(Sender: TObject);
var
    sql,sendmsg,backinfo,errorinfo:string;
  mobanid,mobile,txt1,txt2,txt3,txt4,logtxt:string;
  F : Textfile;
  id:integer;
begin
  logtxt:='duglog:';
  sql:='update C_SMSSend set flag=1,send_time=getdate() where id in(-1,';
   if not IsSending then
   begin
       IsSending:=true;
       query.Close;
       query.SQL.Clear;
       query.SQL.Add('select * from C_SMSSend where flag = 0');
       query.Open;

       while not query.Eof do
       begin
            id:=query.FieldByName('id').AsInteger;
            mobanid:=query.FieldByName('mobanid').AsString;
            mobile:=query.FieldByName('mobile').AsString;
            txt1:=query.FieldByName('txt1').AsString;
            txt2:=query.FieldByName('txt2').AsString;
            txt3:=query.FieldByName('txt3').AsString;
            txt4:=query.FieldByName('txt4').AsString;


            sendmsg:='http://www.goushuji.com/timinc/sendsms.php?mobile='+mobile+'&mobanid='+mobanid+'&txt1='+HTTPEncode(UTF8Encode(txt1))+'&txt2='+HTTPEncode(UTF8Encode(txt2))+'&txt3='+HTTPEncode(UTF8Encode(txt3))+'&txt4='+HTTPEncode(UTF8Encode(txt4))+'';
            backinfo:=GetUrl.Get(sendmsg);
            sleep(2000);
           logtxt:=logtxt+'id:'+IntToStr(id)+sendmsg;
            if backinfo='yes' then
            begin
               sql:=sql+ intToStr(id) +',';
            end else
            begin
                 errorinfo:=backinfo;
                writetxt(errorinfo+'::::'+logtxt);
            end;

           query.Next;
       end;
     if query.RecordCount<>0 then
     begin
       adoexe.Close;
       adoexe.SQL.Clear;
       adoexe.SQL.Add(sql+'-1)');
       adoexe.ExecSQL;
     end;
       IsSending:=false;



   end;

end;

procedure TSMService.writetxt(txt:string);
Var
 F: Textfile;
begin
   AssignFile(F,'D:\book\log.txt'); {将文件名与变量 F 关联}
Append(F); {以编辑方式打开文件 F }
Writeln(F,txt);
Closefile(F); {关闭文件 F}

end;

end.
