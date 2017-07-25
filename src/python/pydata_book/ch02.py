import json
path = 'ch02/usagov_bitly_data2012-03-16-1331923249.txt'
records = [json.loads(line) for line in open(path)]
#print(records[0])
print(records[0]['tz'])

time_zones = [rec['tz'] for rec in records if 'tz' in rec]
for tz_ in time_zones[:10]:
    print(tz_)

def get_counts(sequence):
    counts = {}
    for x in sequence:
        if x in counts:
            counts[x] += 1
        else:
            counts[x] = 1
    return counts

from collections import defaultdict
def get_counts2(sequence):
    counts = defaultdict(int)
    for x in sequence:
        counts[x] += 1
    return counts

counts = get_counts(time_zones)
print(counts['America/New_York'])
print(len(time_zones))

def top_counts(count_dict, n=10):
    value_key_pairs = [(count, tz) for tz, count in count_dict.items()]
    value_key_pairs.sort()
    return value_key_pairs[-n:]

for top_item in top_counts(counts):
    print(top_item)

from collections import Counter
counts = Counter(time_zones)
for sortc in counts.most_common(10):
    print(sortc)




