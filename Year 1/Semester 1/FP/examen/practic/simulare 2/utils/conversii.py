from datetime import date, time
def conversieData(dataStr):
    """
    0123456789
    dd.MM.yyyy
    """
    zi = int(dataStr[:2])
    luna = int(dataStr[3:5])
    an = int(dataStr[6:])
    dataFormat = date(an, luna, zi)
    return dataFormat

def conversieTimp(timpStr):
    """
    hh:mm
    """
    ora = int(timpStr[:2])
    minute = int(timpStr[3:])

    oraFormat = time(ora, minute)
    return oraFormat

