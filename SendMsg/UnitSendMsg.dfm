object SMService: TSMService
  OldCreateOrder = False
  DisplayName = 'SendMMS'
  OnStart = ServiceStart
  Height = 226
  Width = 227
  object con: TADOConnection
    ConnectionString = 
      'Provider=SQLOLEDB.1;Password=pdz@c3$9w4!0tb19;Persist Security I' +
      'nfo=True;User ID=sa;Initial Catalog=book;Data Source=112.74.77.5' +
      '0'
    LoginPrompt = False
    Provider = 'SQLOLEDB.1'
    Left = 72
    Top = 56
  end
  object query: TADOQuery
    Connection = con
    Parameters = <>
    Left = 136
    Top = 56
  end
  object timer: TTimer
    Interval = 300000
    OnTimer = timerTimer
    Left = 24
    Top = 56
  end
  object adoexe: TADOQuery
    Connection = con
    Parameters = <>
    Left = 112
    Top = 8
  end
  object GetUrl: TIdHTTP
    AllowCookies = True
    ProxyParams.BasicAuthentication = False
    ProxyParams.ProxyPort = 0
    Request.ContentLength = -1
    Request.ContentRangeEnd = -1
    Request.ContentRangeStart = -1
    Request.ContentRangeInstanceLength = -1
    Request.Accept = 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'
    Request.BasicAuthentication = False
    Request.UserAgent = 'Mozilla/3.0 (compatible; Indy Library)'
    Request.Ranges.Units = 'bytes'
    Request.Ranges = <>
    HTTPOptions = [hoForceEncodeParams]
    Left = 128
    Top = 112
  end
end
